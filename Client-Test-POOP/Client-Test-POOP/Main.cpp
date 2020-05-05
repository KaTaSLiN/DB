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
#include <mysql.h>

//De pe Server
#include "CResult.h"

using namespace std;

int main(void)
{
    sf::IpAddress ip = sf::IpAddress("localhost");
    sf::TcpSocket socket;
    bool Done = false;
    std::string userName, passWord;
    std::string mod;
    int mode;

    std::cout << "1 For LogIn." << std::endl << "2 for Register." << std::endl << "Enter your choice: ";
    std::getline(std::cin, mod);
    std::cout << "Enter a User Name: ";
    std::getline(std::cin, userName);
    std::cout << "Enter a Password: ";
    std::getline(std::cin, passWord);

    mode = std::stoi(mod);

    sf::Packet packetToSend;
    packetToSend << mode << userName << passWord;

    if (socket.connect(ip, 2000) == sf::Socket::Done)
    {
        socket.send(packetToSend);
        socket.setBlocking(false);

        std::string command;

        std::cout << "Enter a Command: ";
        std::getline(std::cin, command);
        packetToSend.clear();
        if (packetToSend << command)
        {
            socket.send(packetToSend);
            socket.setBlocking(false);
        }
        sf::Packet packetReceived;

        while (!Done)
        {
            packetReceived.clear();
            if (socket.receive(packetReceived) == sf::Socket::Done)
            {
                CResult res;
                if (packetReceived >> res)
                {
                    if (res.getNumberOfFields() > 0)
                    {
                        for (unsigned int j = 0; j < res.getNumberOfFields(); j++)
                        {
                            printf("%s ", res.getFieldName(j));
                        }
                        std::cout << std::endl;
                        for (unsigned int i = 0; i < res.getNumberOfRows(); i++)
                        {
                            for (unsigned int j = 0; j < res.getNumberOfFields(); j++)
                            {
                                printf("%s ", res[i][j]);
                            }
                            std::cout << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Rows affected: " << res.getNumberOfRows() << std::endl;
                    }

                }

                std::cout << "Enter a Command: ";
                std::getline(std::cin, command);
                packetToSend.clear();
                if (packetToSend << command)
                {
                    socket.send(packetToSend);
                    socket.setBlocking(false);
                }
            }
        }
    }
    else
    {
        //Error
        std::cout << "Nu s-a reusit conectarea la server!" << std::endl;
    }
    return 0;
}


//int main(void)
//{
//    sf::IpAddress ip = sf::IpAddress("localhost");
//    sf::TcpSocket socket;
//    bool Done = false;
//    std::string text;
//
//    std::cout << "Enter a User Name: ";
//    std::getline(std::cin, text);
//    socket.connect(ip, 2000);
//
//    sf::Packet packetToSend;
//    packetToSend << text;
//    socket.send(packetToSend);
//    socket.setBlocking(false);
//
//    while (!Done)
//    {
//        sf::Packet packetReceived;
//        std::string command;
//
//        std::cout << "Enter a Command: ";
//        std::getline(std::cin, command);
//        std::cout << command;
//        packetToSend.clear();
//        if (packetToSend << command)
//        {
//            socket.send(packetToSend);
//            socket.setBlocking(false);
//            Done = true;
//        }
//        if (socket.receive(packetReceived) == sf::Socket::Done)
//        {
//            //std::string tempText;
//            /*if (packetReceived >> tempText)
//            {
//                std::cout << tempText << std::endl;
//            }*/
//          
//            packetReceived.clear();
//            if (socket.receive(packetReceived) == sf::Socket::Done)
//            {
//                CResult res;
//                packetReceived >> res;
//                for (unsigned int i = 0; i < res.getNumberOfRows(); i++)
//                {
//                    for (unsigned int j = 0; j < res.getNumberOfFields(); j++)
//                    {
//                        printf("%s ", res[i][j]);
//                    }
//                    std::cout << std::endl;
//
//                }
//                Done = true;
//            }
//
//        }
//    }
//    return 0;
//}