#pragma once
#include "CCredentials.h"
#include <vector>

class CLoginManager
{
public:
	enum Mode
	{
		ModeLogIn = 1,
		ModeRegister = 2
	};
public:
	//Constructors
	CLoginManager();
	~CLoginManager();
	CLoginManager(const CLoginManager&) = delete;

	//Functions

	//Returneaza True daca inregistrarea utilizatorului a reusit
	//Returneaza False daca utilizatorul deja exista
	bool regUser(CCredentials crd);
	//Returneaza True daca logarea utilizatorului a reusit
	//Returneaza False daca credentialele utilizatorului sunt gresite
	bool loginUser(CCredentials crd);

private:
	//Members
	std::vector<CCredentials> m_Credentials;
	//Functions

	//Returneaza True daca credentialele exista in database
	//Returneaza False daca credentialele nu exista in database
	bool f_AccountExists(CCredentials attempt);
	bool f_UserExists(CCredentials attempt);
	void f_writeInFile(CCredentials crd);
	void f_readFile();


};

