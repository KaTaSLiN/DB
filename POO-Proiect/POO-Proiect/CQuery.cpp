#include "CQuery.h"
#include <iostream>

CQuery::CQuery() : m_Query(""), m_Result(nullptr, 0, 0)
{
}

CQuery::CQuery(std::string Query) : m_Query(Query), m_Result(nullptr, 0, 0)
{
}

CQuery::CQuery(const char* Query) : m_Query(Query), m_Result(nullptr, 0, 0)
{
}

CQuery::~CQuery()
{
}

CResult CQuery::getResult()
{
	return m_Result;
}

std::string CQuery::getQuery()
{
	return m_Query;
}

void CQuery::setQuery(std::string Query)
{
	this->m_Query = Query;
}

void CQuery::setQuery(const char* Query)
{
	this->m_Query = Query;
}

CQuery& CQuery::operator=(const CQuery& Query)
{
	if (this != &Query)
	{
		this->m_Query = Query.m_Query;
		this->m_Result.clear();
	}
	return *this;
}

CQuery& CQuery::operator=(const std::string Query)
{
	if (this->m_Query != Query)
	{
		this->m_Query = Query;
		this->m_Result.clear();
	}
	return *this;
}

CQuery& CQuery::operator=(const char* Query)
{
	if (!strcmp(this->m_Query.c_str(), Query) == 0)
	{
		this->m_Query = Query;
		this->m_Result.clear();
	}
	return *this;
}

CQuery& CQuery::operator+=(const CQuery& Query)
{
	if (this != &Query)
	{
		this->m_Query += Query.m_Query;
		this->m_Result.clear();
	}
	return *this;
}

CQuery& CQuery::operator+=(const std::string Query)
{
	if (this->m_Query != Query)
	{
		this->m_Query += Query;
		this->m_Result.clear();
	}
	return *this;
}

CQuery& CQuery::operator+=(const char* Query)
{
	if (!(strcmp(this->m_Query.c_str(), Query) == 0))
	{
		this->m_Query += Query;
		this->m_Result.clear();
	}
	return *this;
}

void CQuery::clear()
{
	this->m_Query.clear();
	this->m_Result.clear();
}

int CQuery::ask(MYSQL* DataBase)
{
	MYSQL_ROW row;
	MYSQL_FIELD* field;
	int c = 0;
	if (DataBase)
	{
		//this->m_Query = "SELECT * FROM members;";
		c = mysql_query(DataBase, this->m_Query.c_str());
		if (c)
		{
			// ERROR
			std::cout << "Eroare MYSQL_QUERY: "<< mysql_error(DataBase) << std::endl;

		}
		else // query succeeded, process any data returned by it
		{
			this->m_Result = mysql_store_result(DataBase);

			if (this->m_Result.getResultPtr())  // there are rows
			{
				// retrieve rows, then call mysql_free_result(result)
				while (field = this->m_Result.extractField())
				{
					this->m_Result.addField(field->name);
				}
				while (row = this->m_Result.extractRow())
				{
					this->m_Result.addRow(row);
				}
			}
			else  //mysql_store_result() returned nothing; should it have?
			{
				if (this->getResult().getNumberOfFields() == 0)
				{
					// query does not return data
					// (it was not a SELECT)
					this->m_Result.setNumberOfRows(mysql_affected_rows(DataBase));
				}
				else // mysql_store_result() should have returned data
				{
					// ERROR
					std::cout << "Eroare nu returneaza date si ar fi trebuit!" << std::endl;

					//fprintf(stderr, "Error: %s\n", mysql_error(DataBase));
				}
			}

			mysql_free_result(this->m_Result.getResultPtr());
		}
	}
	return c;
}
