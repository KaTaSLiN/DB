#pragma once
#include "IQuery.h"
#include <string>
#include <mysql.h>
#include "CResult.h"

class CQuery :
	public IQuery
{
public:
	CQuery();
	CQuery(std::string Query);
	CQuery(const char* Query);
	~CQuery();

	//Getters
	CResult getResult();
	std::string getQuery();

	//Setters
	void setQuery(std::string Query);
	void setQuery(const char* Query);

	//Overload
	//friend sf::Packet& operator<<(sf::Packet& packet, const CQuery& q);
	//friend sf::Packet& operator>>(sf::Packet& packet, CQuery& q);


	CQuery& operator= (const CQuery& Query);
	CQuery& operator= (const std::string Query);
	CQuery& operator= (const char* Query);
	CQuery& operator+= (const CQuery& Query);
	CQuery& operator+= (const std::string Query);
	CQuery& operator+= (const char* Query);

	//Functions
	void clear();
	int ask(MYSQL* DataBase);

private:
	std::string m_Query;
	CResult m_Result;
};

