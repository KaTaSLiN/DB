#pragma once
#include "IDataBase.h"
#include <mysql.h>
#include <string>
#include "CCredentials.h"

class CDataBase :
	public IDataBase
{
public:
	//Constructors
	CDataBase(const char* Host, const char* User, const char* Password, const char* DataBaseName, unsigned int Port);
	CDataBase(std::string Host, std::string User, std::string Password, std::string DataBaseName, unsigned int Port);
	CDataBase(const char* Host, CCredentials Credentials, const char* DataBaseName, unsigned int Port);
	CDataBase(std::string Host, CCredentials Credentials, std::string DataBaseName, unsigned int Port);
	CDataBase(const CDataBase&) = delete;
	~CDataBase();

	//Getters
	MYSQL* getConnection();
	CCredentials getCredentials();

	//Setters
	//

	//Functions 
	void closeConnection();
private:
	//members
	MYSQL* m_Connection;
	CCredentials m_Credentials;
	std::string m_Host;
	std::string m_DataBaseName;
	unsigned int m_Port;
	//functions
};

