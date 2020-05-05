#include "CLoginManager.h"
#include "CUserBase.h"
#include <fstream>
#include <iostream>
#define db "users.txt"


CLoginManager::CLoginManager()
{
	f_readFile();
}

CLoginManager::~CLoginManager()
{
}

bool CLoginManager::regUser(CCredentials crd)
{
	if (f_UserExists(crd))
	{
		return false;
	}
	else
	{
		//Introduce utilizatorul in database
		f_writeInFile(crd);
		return true;
	}
}

bool CLoginManager::loginUser(CCredentials crd)
{
	if (f_AccountExists(crd))
		return true;
	else
		return false;
}

bool CLoginManager::f_AccountExists(CCredentials attempt)
{
	for (int i = 0; i < this->m_Credentials.size(); i++)
		if (attempt.getUserName() == m_Credentials[i].getUserName() && attempt.getPassword() == m_Credentials[i].getPassword())
			return true;
	return false;
}

bool CLoginManager::f_UserExists(CCredentials attempt)
{
	for (int i = 0; i < this->m_Credentials.size(); i++)
		if (attempt.getUserName() == m_Credentials[i].getUserName())
			return true;
	return false;
}

void CLoginManager::f_writeInFile(CCredentials crd)
{
	std::fstream file(db, std::ios::app);
	if (file.is_open())
	{
		file << std::endl;
		file << crd.getUserName() << " " << crd.getPassword();
		file.close();
	}
	else
	{
		//Eroare
	}
}

void CLoginManager::f_readFile()
{
	std::fstream file(db, std::ios::in);
	std::string user, pass, ver;
	if (file.is_open())
	{
		while (file.good())
		{
			file >> user;
			file >> pass;
			CCredentials crd(user, pass);
			this->m_Credentials.push_back(crd);
		}
	}
	else
	{
		//Error
		std::cout << "Nu s-a deschis fisierul" << std::endl;
	}
}
