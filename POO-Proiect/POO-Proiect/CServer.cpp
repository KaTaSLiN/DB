#include "CServer.h"
#include<iostream>
#include "CQuery.h"

void CServer::initServer(unsigned short Port)
{
	this->m_Port = Port;
	this->m_Listener.listen(this->m_Port);
	this->m_Selector.add(m_Listener);
}

void CServer::closeServer()
{
	for (std::vector<sf::TcpSocket*>::iterator it = m_Clients.begin(); it != m_Clients.end(); it++)
		delete* it;
}

bool CServer::sendPackets()
{
	//Trimiterea Packetelor procesate
	bool didSend = false;
	while (!m_PacketsToSend.empty())
	{
		m_Clients[m_PacketsToSend.back().first]->send(m_PacketsToSend.back().second);
		m_PacketsToSend.pop_back();
		didSend = true;
	}
	return didSend;
}

bool CServer::receivePackets()
{
	//Obtinerea de Packete
	bool didReceive = false;
	for (int i = 0; i < m_Clients.size(); i++)
	{
		if (m_Selector.isReady(*m_Clients[i]))
		{
			sf::Packet packet;
			if (m_Clients[i]->receive(packet) == sf::Socket::Done)
			{
				this->m_PacketsReceived.push_back(std::make_pair(i, packet));
				didReceive = true;
			}
		}
	}
	return didReceive;
}

bool CServer::processPackets(MYSQL* DBConnection)
{
	bool didProcess = false;
	while (!m_PacketsReceived.empty())
	{
		if (DBConnection)
		{
			std::string text;
			m_PacketsReceived.back().second >> text;
			CQuery query(text);
			query.ask(DBConnection);

			//Process
			//Afisare Fields
			/*for (unsigned int i = 0; i < query.getResult().getNumberOfFields(); i++)
			{
				printf("%s ", query.getResult().getFieldName(i));
			}
			//End Afisare Fields

			std::cout << std::endl;

			//Afisare Tabel
			for (unsigned int i = 0; i < query.getResult().getNumberOfRows(); i++)
			{
				for (unsigned int j = 0; j < query.getResult().getNumberOfFields(); j++)
				{
					printf("%s ", query.getResult()[i][j]);
				}
				std::cout << std::endl;
			}*/
			//End Afisare Tabel
			//End Process

			sf::Packet packetToSend;
			packetToSend << query.getResult();
			m_PacketsToSend.push_back(std::make_pair(m_PacketsReceived.back().first, packetToSend));
			m_PacketsReceived.pop_back();
			query.clear();
			didProcess = true;
		}
		else
		{
			//ERROR
			std::cout << "Conexiunea este inchisa!";
		}
	}
	return didProcess;
}

bool CServer::waitForConnections()
{
	//Stabilirea conexiunii
	if (this->m_Selector.wait())
	{
		if (this->m_Selector.isReady(this->m_Listener))
		{
			sf::TcpSocket* Socket = new sf::TcpSocket;
			this->m_Listener.accept(*Socket);
			sf::Packet packetReceived;
			std::string id;
			if (Socket->receive(packetReceived) == sf::Socket::Done)
				if (packetReceived >> id)
				{
					std::cout << id << " has connected to the Server!" << std::endl;
					this->m_Clients.push_back(Socket);
					this->m_Selector.add(*Socket);

					////Send confirmation
					//sf::Packet packetToSend;
					//packetToSend << "Welcome on the Server!";
					//Socket->send(packetToSend);
					return true;
				}
		}
		else
		{
			return !this->receivePackets();
		}
	}
	return false;
}

sf::Packet CServer::getPackets()
{
	if (!m_PacketsReceived.empty())
		return this->m_PacketsReceived.back().second;
	else
		return sf::Packet();
}

void CServer::addPacketToSend(sf::Packet& packet)
{
	if (packet)
		this->m_PacketsToSend.push_back(std::make_pair(this->m_PacketsReceived.back().first, packet));
}
