#pragma once
#include "IServer.h"
#include <vector>
#include <utility>
class CServer :
	public IServer
{
public:
	//Constructors
	CServer() { ; }
	~CServer() { ; }

	//Functions
	void initServer(unsigned short Port) override;
	void closeServer() override;
	bool sendPackets() override;
	bool receivePackets() override;
	bool processPackets(MYSQL* DBConnection) override;
	bool waitForConnections() override;

	//Getters
	virtual sf::Packet getPackets() override; //Trebuie sa intoarca un pointer la vectorul de packete primite pentru a fi procesate

	//Setters
	void addPacketToSend(sf::Packet& packet); //Trebuie adaugat catre cine sa fie trimis


private:
	
	CServer(CServer&) = delete;
	//members
	unsigned short m_Port = 2000;
	sf::TcpListener m_Listener;
	sf::SocketSelector m_Selector;
	std::vector<sf::TcpSocket*> m_Clients;
	std::vector<std::pair<int, sf::Packet>> m_PacketsReceived; //int trebuie schimbat cu un identificator de client unic 
	std::vector<std::pair<int, sf::Packet>> m_PacketsToSend; //int trebuie schimbat cu un identificator de client unic 
};

