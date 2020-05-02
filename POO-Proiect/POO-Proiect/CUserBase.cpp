#include "CUserBase.h"

CUserBase::CUserBase():m_Credentials()
{
}

CUserBase::CUserBase(const CUserBase& other) : m_Credentials(other.m_Credentials)
{
}

CUserBase::CUserBase(CCredentials& Credentials) : m_Credentials(Credentials)
{
}

CUserBase::CUserBase(std::string Password) : m_Credentials(Password)
{
}

CUserBase::CUserBase(std::string UserName, std::string Password) : m_Credentials(UserName, Password)
{
}

CUserBase::CUserBase(const char* UserName, const char* Password) : m_Credentials(UserName, Password)
{
}

CUserBase::~CUserBase()
{
}

void CUserBase::setCredentials(std::string UserName, std::string Password)
{
	this->m_Credentials.setUserName(UserName);
	this->m_Credentials.setPassword(Password);
}

void CUserBase::setCredentials(const char* UserName, const char* Password)
{
	this->m_Credentials.setUserName(UserName);
	this->m_Credentials.setPassword(Password);
}

void CUserBase::setUserName(std::string UserName)
{
	this->m_Credentials.setUserName(UserName);
}

void CUserBase::setUserName(const char* UserName)
{
	this->m_Credentials.setUserName(UserName);
}

void CUserBase::setPassword(std::string Password)
{
	this->m_Credentials.setPassword(Password);
}

void CUserBase::setPassword(const char* Password)
{
	this->m_Credentials.setPassword(Password);
}

CCredentials CUserBase::getCredentials()
{
	return this->m_Credentials;
}

std::string CUserBase::getUserName()
{
	return this->m_Credentials.getUserName();
}

std::string CUserBase::getPassword()
{
	return this->m_Credentials.getPassword();
}
