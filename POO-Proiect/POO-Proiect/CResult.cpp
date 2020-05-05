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

char* CResult::getFieldName(unsigned int index)
{
	if (index <= this->m_Fields.size())
		return this->m_Fields[index];
	else
		return this->m_Fields[0];
	return nullptr;
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

void CResult::addField(char* Field)
{
	if (Field != nullptr)
	{
		//Clear this
		char* copy = (char*)malloc((strlen(Field) + 1) * sizeof(char));
		strncpy(copy, Field, strlen(Field));
		copy[strlen(Field)] = '\0';
		this->m_Fields.push_back(copy);
	}
	else
	{
		//Clear this
		char* copy = (char*)malloc((strlen("No name") + 1) * sizeof(char));
		strncpy(copy, "No name", strlen("No name"));
		copy[strlen("No name")] = '\0';
		this->m_Fields.push_back(copy);
	}
}

MYSQL_FIELD* CResult::extractField()
{
	return mysql_fetch_field(this->m_ResultPtr);
}

void CResult::addRow(MYSQL_ROW Row)
{
	//Update
	if (Row != nullptr)
	{
		//Clear this
		char** copy = (char**)malloc((this->m_NumberOfFields) * sizeof(char*));
		for (unsigned int j = 0; j < this->m_NumberOfFields; j++)
		{
			if (Row[j] != nullptr)
			{
				//Clear this
				copy[j] = (char*)malloc((strlen(Row[j]) + 1) * sizeof(char));
				strncpy(copy[j], Row[j], strlen(Row[j]));
				copy[j][strlen(Row[j])] = '\0';
			}
			else
			{
				//Clear this
				copy[j] = (char*)malloc((strlen("NULL") + 1) * sizeof(char));
				strncpy(copy[j], "NULL", strlen("NULL"));
				copy[j][strlen("NULL")] = '\0';
			}
		}
		this->m_Rows.push_back(copy);
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
	if (r.m_NumberOfFields > 0 && r.m_NumberOfRows > 0)
	{
		for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
		{
			if (r.m_Fields[j] != nullptr)
				packet << r.m_Fields[j];
			else
				packet << "No name";
		}
		for (unsigned int i = 0; i < r.m_NumberOfRows; i++)
			for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
			{
				if (r.m_Rows[i][j] != nullptr)
					packet << r.m_Rows[i][j];
				else
					packet << "NULL";
			}
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, CResult& r)
{
	char buff[1000];
	packet >> r.m_NumberOfFields >> r.m_NumberOfRows;
	if (r.m_NumberOfFields > 0 && r.m_NumberOfRows > 0)
	{
		//Fields
		//Clear this
		char** Fields = (char**)malloc((r.m_NumberOfFields) * sizeof(char*));
		for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
		{
			packet >> buff;
			//Field Name
			//Clear this
			Fields[j] = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strncpy(Fields[j], buff, strlen(buff));
			Fields[j][strlen(buff)] = '\0';
			r.addField(Fields[j]);
		}
		//Table
		//Clear this
		char*** Table = (char***)malloc((r.m_NumberOfRows) * sizeof(char**));
		for (unsigned int i = 0; i < r.m_NumberOfRows; i++)
		{
			//Row
			//Clear this
			Table[i] = (char**)malloc((r.m_NumberOfFields) * sizeof(char*));
			for (unsigned int j = 0; j < r.m_NumberOfFields; j++)
			{
				packet >> buff;
				//Field
				//Clear this
				Table[i][j] = (char*)malloc((strlen(buff) + 1) * sizeof(char));
				strncpy(Table[i][j], buff, strlen(buff));
				Table[i][j][strlen(buff)] = '\0';
			}
			r.addRow(Table[i]);
		}
	}
	return packet;
}
