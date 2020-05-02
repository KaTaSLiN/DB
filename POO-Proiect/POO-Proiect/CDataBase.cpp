#include "CDataBase.h"

CDataBase::CDataBase(const char* Host, const char* User, const char* Password, const char* DataBaseName, unsigned int Port)
	:m_Host(Host), m_Credentials(User,Password), m_DataBaseName(DataBaseName), m_Port(Port)
{
	this->m_Connection = mysql_init(0);
	this->m_Connection = mysql_real_connect(
		this->m_Connection, m_Host.c_str(),
		m_Credentials.getUserName().c_str(),
		m_Credentials.getPassword().c_str(),
		m_DataBaseName.c_str(),
		m_Port, NULL, CLIENT_MULTI_STATEMENTS);
}

CDataBase::CDataBase(std::string Host, std::string User, std::string Password, std::string DataBaseName, unsigned int Port)
	: m_Host(Host), m_Credentials(User, Password), m_DataBaseName(DataBaseName), m_Port(Port)

{
	this->m_Connection = mysql_init(0);
	this->m_Connection = mysql_real_connect(
		this->m_Connection, m_Host.c_str(),
		m_Credentials.getUserName().c_str(),
		m_Credentials.getPassword().c_str(),
		m_DataBaseName.c_str(),
		m_Port, NULL, CLIENT_MULTI_STATEMENTS);
}

CDataBase::CDataBase(const char* Host, CCredentials Credentials, const char* DataBaseName, unsigned int Port)
	: m_Host(Host), m_Credentials(Credentials), m_DataBaseName(DataBaseName), m_Port(Port)

{
	this->m_Connection = mysql_init(0);
	this->m_Connection = mysql_real_connect(
		this->m_Connection, m_Host.c_str(),
		m_Credentials.getUserName().c_str(),
		m_Credentials.getPassword().c_str(),
		m_DataBaseName.c_str(),
		m_Port, NULL, CLIENT_MULTI_STATEMENTS);
}

CDataBase::CDataBase(std::string Host, CCredentials Credentials, std::string DataBaseName, unsigned int Port)
	: m_Host(Host), m_Credentials(Credentials), m_DataBaseName(DataBaseName), m_Port(Port)

{
	this->m_Connection = mysql_init(0);
	this->m_Connection = mysql_real_connect(
		this->m_Connection, m_Host.c_str(),
		m_Credentials.getUserName().c_str(), 
		m_Credentials.getPassword().c_str(), 
		m_DataBaseName.c_str(),
		m_Port, NULL, CLIENT_MULTI_STATEMENTS);
}

CDataBase::~CDataBase()
{
}

MYSQL* CDataBase::getConnection()
{
	if (m_Connection)
		return m_Connection;
	else
		return nullptr;
}

CCredentials CDataBase::getCredentials()
{
	return m_Credentials;
}

void CDataBase::closeConnection()
{
	if (m_Connection)
		mysql_close(m_Connection);
}
