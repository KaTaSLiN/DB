#pragma once
#include "ICredentials.h"
#include <string>
class CCredentials :
	public ICredentials
{
public:
	//Constructors
	CCredentials();
	CCredentials(const CCredentials&);
	CCredentials(std::string Password);
	CCredentials(std::string UserName, std::string Password);
	~CCredentials();

	//Setters
	void setUserName(std::string UserName);
	void setUserName(const char* UserName);
	void setPassword(std::string Password);
	void setPassword(const char* Password);

	//Getters
	std::string getUserName();
	std::string getPassword();

private:
	std::string m_UserName;
	std::string m_Password;
};

