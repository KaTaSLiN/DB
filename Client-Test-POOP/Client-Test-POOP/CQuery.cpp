#include "CQuery.h"

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

	if (DataBase)
	{
		//this->m_Query = "SELECT * FROM members;";

		if (mysql_query(DataBase, this->m_Query.c_str()))
		{
			// ERROR
		}
		else // query succeeded, process any data returned by it
		{
			this->m_Result = mysql_store_result(DataBase);

			if (this->m_Result.getResultPtr())  // there are rows
			{
				// retrieve rows, then call mysql_free_result(result)
				while (row = this->m_Result.extractRow())
				{
					//Pentru a merge cu std::cout poate trebuie aici facut ceva inainte sa adaug ??
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

					//fprintf(stderr, "Error: %s\n", mysql_error(DataBase));
				}
			}
		}
	}
	return mysql_query(DataBase, this->m_Query.c_str());
}

 //sf::Packet& operator <<(sf::Packet& packet, const CQuery& q)
 //{
 //    return packet << q.m_Query << q.m_Result;
 //}

 //sf::Packet& operator >>(sf::Packet& packet, CQuery& q)
 //{
	// return packet >> q.m_Query >> q.m_Result;
 //}
