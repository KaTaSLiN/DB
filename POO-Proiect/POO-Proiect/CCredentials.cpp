#include "CCredentials.h"

CCredentials::CCredentials():m_UserName("Guest"),m_Password("guest")
{
}

CCredentials::CCredentials(const CCredentials& other):m_UserName(other.m_UserName),m_Password(other.m_Password)
{
}

CCredentials::CCredentials(std::string Password):m_UserName("Guest"),m_Password(Password)
{
}

CCredentials::CCredentials(std::string UserName, std::string Password):m_UserName(UserName),m_Password(Password)
{
}

CCredentials::~CCredentials()
{
}

void CCredentials::setUserName(std::string UserName)
{
	this->m_UserName = UserName;
}

void CCredentials::setUserName(const char* UserName)
{
	this->m_UserName = UserName;
}

void CCredentials::setPassword(std::string Password)
{
	this->m_Password = Password;
}

void CCredentials::setPassword(const char* Password)
{
	this->m_Password = Password;
}

std::string CCredentials::getUserName()
{
	return this->m_UserName;
}

std::string CCredentials::getPassword()
{
	return this->m_Password;
}
