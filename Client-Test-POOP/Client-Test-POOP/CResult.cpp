#define _CRT_SECURE_NO_WARNINGS
#include "CResult.h"

CResult::CResult() : CResult(nullptr, 0, 0)
{
}

CResult::CResult(MYSQL_RES* ResultPtr, unsigned int NumberOfFields, uint64_t NumberOfRows)
	: m_ResultPtr(ResultPtr), m_NumberOfFields(NumberOfFields), m_NumberOfRows(NumberOfRows)
{
}

CResult::~CResult()
{
}

MYSQL_RES* CResult::getResultPtr()
{
	return this->m_ResultPtr;
}

unsigned int CResult::getNumberOfFields()
{
	return m_NumberOfFields;
}

uint64_t CResult::getNumberOfRows()
{
	return this->m_NumberOfRows;
}

void CResult::setResultPtr(MYSQL_RES* ResultPtr)
{
	this->m_ResultPtr = ResultPtr;
}

void CResult::setNumberOfFields(unsigned int NumberOfFields)
{
	this->m_NumberOfFields = NumberOfFields;
}

void CResult::setNumberOfRows(uint64_t NumberOfRows)
{
	this->m_NumberOfRows = NumberOfRows;
}

MYSQL_ROW CResult::extractRow()
{
	return mysql_fetch_row(this->m_ResultPtr);
}

MYSQL_FIELD* CResult::extractField()
{
	return mysql_fetch_field(this->m_ResultPtr);
}

void CResult::addRow(MYSQL_ROW Row)
{
	if (Row != nullptr)
	{
		this->m_Rows.push_back(Row);
	}
}

void CResult::clear()
{
	this->m_ResultPtr = nullptr;
	this->m_NumberOfFields = 0;
	this->m_NumberOfRows = 0;
	this->m_Rows.clear();
}

CResult& CResult::operator=(MYSQL_RES* ResultPtr)
{
	if (this->m_ResultPtr != ResultPtr)
	{
		this->m_ResultPtr = ResultPtr;
		this->m_NumberOfFields = mysql_num_fields(ResultPtr);
		this->m_NumberOfRows = mysql_num_rows(ResultPtr);

		/*MYSQL_ROW Row;
		while (Row = this->extractRow())
			this->addRow(Row);*/
	}
	return *this;
}

MYSQL_ROW& CResult::operator[](unsigned int index)
{
	if (index <= this->m_Rows.size())
		return this->m_Rows[index];
	else
		return this->m_Rows[0];
}

sf::Packet& operator<<(sf::Packet& packet, const CResult& r)
{
	packet << r.m_NumberOfFields << r.m_NumberOfRows;
	for (unsigned int i = 0; i < r.m_NumberOfRows; i++)
		for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
		{
			if (r.m_Rows[i][j] != nullptr)
				packet << r.m_Rows[i][j];
			else
				packet << "NULL";
		}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, CResult& r)
{
	//Versiune initiala
/*packet >> r.m_NumberOfFields >> r.m_NumberOfRows;
for (unsigned int i = 0; i < r.m_NumberOfRows; i++)
	for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
		packet >> r.m_Rows[i][j];*/


	packet >> r.m_NumberOfFields >> r.m_NumberOfRows;
	char*** Table = (char***)malloc((r.m_NumberOfRows) * sizeof(char**));
	//char** Row = (char**)malloc((r.m_NumberOfFields) * sizeof(char*));
	char buff[1000];
	for (unsigned int i = 0; i < r.m_NumberOfRows; i++)
	{
		Table[i] = (char**)malloc((r.m_NumberOfFields) * sizeof(char*));
		for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
		{
			packet >> buff;
			Table[i][j] = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strncpy(Table[i][j], buff, strlen(buff));
			Table[i][j][strlen(buff)] = '\0';
		}
		r.addRow(Table[i]);
	}

	//Clear memory
	/*for (unsigned int i = 0; i < r.m_NumberOfFields; i++)
		free(Row[i]);
	free(Row);*/

	return packet;
}
