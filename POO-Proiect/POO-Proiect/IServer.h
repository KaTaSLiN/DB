#pragma once
#include <SFML/Network.hpp>
#include <mysql.h>

class IServer
{
public:
	virtual void initServer(unsigned short Port) = 0;
	virtual bool waitForConnections() = 0;
	virtual sf::Packet getPackets() = 0;
	virtual bool sendPackets() = 0;
	virtual bool processPackets(MYSQL* DBConnection) = 0;
	virtual bool receivePackets() = 0;
	virtual void closeServer() = 0;
};

