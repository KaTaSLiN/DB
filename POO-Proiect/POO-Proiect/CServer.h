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
	CServer(CServer&) = delete;

	//Functions
	void initServer(unsigned short Port) override;
	void closeServer() override;
	//Returneaza True daca a reusit sa trimita cel putin un packet
	bool sendPackets() override;
	//Returneaza True daca a primit cel putin un packet
	bool receivePackets() override;
	//Returneaza True daca procesat cel putin un packet
	bool processPackets(MYSQL* DBConnection) override;
	//Returneaza True daca listener-ul e pregatit si un user s-a conectat sau daca listener-ul nu e pragatit si nu s-a procesat niciun packet
	bool waitForConnections() override;

	//Getters
	virtual sf::Packet getPackets() override; //Trebuie sa intoarca un pointer la vectorul de packete primite pentru a fi procesate

	//Setters
	void addPacketToSend(sf::Packet& packet); //Trebuie adaugat catre cine sa fie trimis


private:
	//Members
	unsigned short m_Port = 2000;
	sf::TcpListener m_Listener;
	sf::SocketSelector m_Selector;
	std::vector<sf::TcpSocket*> m_Clients;
	std::vector<std::pair<int, sf::Packet>> m_PacketsReceived; //int trebuie schimbat cu un identificator de client unic 
	std::vector<std::pair<int, sf::Packet>> m_PacketsToSend; //int trebuie schimbat cu un identificator de client unic 

	//Functions
	void f_trackSocket(sf::TcpSocket* sock);
};

