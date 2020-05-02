#pragma once
#include "IResult.h"
#include <mysql.h>
#include <vector>
#include<SFML\Network.hpp>
class CResult :
	public IResult
{
public:
	//Constructors
	CResult();
	CResult(MYSQL_RES* ResultPtr, unsigned int NumberOfFields, uint64_t NumberOfRows);
	~CResult();

	//Getters
	MYSQL_RES* getResultPtr();
	unsigned int getNumberOfFields();
	uint64_t getNumberOfRows();

	//Setters
	void setResultPtr(MYSQL_RES* ResultPtr);
	void setNumberOfFields(unsigned int NumberOfFields);
	void setNumberOfRows(uint64_t NumberOfRows);

	//Overloads
	friend sf::Packet& operator<<(sf::Packet& packet, const CResult& r);
	friend sf::Packet& operator>>(sf::Packet& packet, CResult& r);
	CResult& operator=(MYSQL_RES* ResultPtr);
	MYSQL_ROW& operator[](unsigned int index);

	//Functions
	void addRow(MYSQL_ROW Row);
	MYSQL_ROW extractRow();
	MYSQL_FIELD* extractField();
	void clear();

private:
	//Members
	MYSQL_RES* m_ResultPtr;
	unsigned int m_NumberOfFields;
	uint64_t m_NumberOfRows;
	std::vector<MYSQL_ROW> m_Rows;

	//Private Functions
	

};

