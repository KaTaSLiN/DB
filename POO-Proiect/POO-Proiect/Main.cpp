#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/* SFML */
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include <iostream>
#include "Global.h"
using namespace std;

//DataBase
#include <mysql.h>
#include "CDataBase.h"
#include "CQuery.h"

//Server
#include "CServer.h"

//int main()
//{
//    CDataBase db(DBHost.c_str(), DBUser.c_str(), DBPass.c_str(), DBName.c_str(), DBport);
//   /* if (db.getConnection())
//    {
//        CQuery q("Select * from members");
//        q.ask(db.getConnection());
//
//        for (int i = 0; i < q.getResult().getNumberOfRows(); i++)
//        {
//            printf("ID: %s.Name is %s , Sex %s  \n", q.getResult()[i][0], q.getResult()[i][1], q.getResult()[i][2]);
//        }
//    }*/
//
//    CServer server;
//    server.initServer(2000);
//    bool Done = false;
//
//    string text1;
//
//    while (!Done)
//    {
//        if (!server.waitForConnections())
//        {
//            if (server.getPackets() >> text1)
//                std::cout << text1 << std::endl;
//            CQuery query(text1);
//            if (db.getConnection())
//            {
//                query.ask(db.getConnection());
//
//               /* for (int i = 0; i < query.getResult().getNumberOfRows(); i++)
//                {
//                    printf("ID: %s.Name is %s , Sex %s  \n", query.getResult()[i][0], query.getResult()[i][1], query.getResult()[i][2]);
//                }*/
//                for (unsigned int i = 0; i < query.getResult().getNumberOfRows(); i++)
//                {
//                    for (unsigned int j = 0; j < query.getResult().getNumberOfFields(); j++)
//
//                    {
//                       printf("%s ", query.getResult()[i][j]);
//                       //std::cout << query.getResult()[i][j] << " ";
//                    }
//                    std::cout << std::endl;
//                }
//            }
//            Done = true;
//        }
//    }
//    server.closeServer();
//
//    return 0;
//}

//VERSIUNE FUNCTIONALA FINALA
//int main()
//{
//    CDataBase db(DBHost.c_str(), DBUser.c_str(), DBPass.c_str(), DBName.c_str(), DBport);
//    if (db.getConnection())
//    {
//        CQuery query("Select * from members");
//        query.ask(db.getConnection());
//
//        for (unsigned int i = 0; i < query.getResult().getNumberOfRows(); i++)
//        {
//            for (unsigned int j = 0; j < query.getResult().getNumberOfFields(); j++)
//            {
//                //std::cout << query.getResult()[i][j] << " ";
//                printf("%s ", query.getResult()[i][j]);
//            }
//            std::cout << std::endl;
//        }
//    }
//    return 0;
//}

int main()
{
    CDataBase db(DBHost.c_str(), DBUser.c_str(), DBPass.c_str(), DBName.c_str(), DBport);
    CServer server;
    server.initServer(2000);
    bool Done = false;

    while (!Done)
    {
        if (db.getConnection())
        {
            if (server.waitForConnections())
            {   
                //Un utilizator se conecteaza sau trimite packete si vor fi receptionate
            }
            else
            {
                server.processPackets(db.getConnection());
                server.sendPackets();
            }
        }
    }
    server.closeServer();

    return 0;
}