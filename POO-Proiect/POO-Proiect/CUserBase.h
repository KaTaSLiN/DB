#pragma once
#include "IUser.h"
#include "CCredentials.h"
class CUserBase :
	public IUser
{
public:
	//Constructors
	CUserBase();
	CUserBase(const CUserBase&);
	CUserBase(CCredentials&);
	CUserBase(std::string Password);
	CUserBase(std::string UserName, std::string Password);
	CUserBase(const char* UserName, const char* Password);
	~CUserBase();

	//Setters
	void setCredentials(std::string UserName, std::string Password);
	void setCredentials(const char* UserName, const char* Password);
	void setUserName(std::string UserName);
	void setUserName(const char* UserName);
	void setPassword(std::string Password);
	void setPassword(const char* Password);

	//Getters
	CCredentials getCredentials();
	std::string getUserName();
	std::string getPassword();
private:
	CCredentials m_Credentials;

};

