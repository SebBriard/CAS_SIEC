#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <list>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#ifndef WIFI_SERV_H
#define WIFI_SERV_H


class WiFiServer
{
public :
    WiFiServer() ;
    ~WiFiServer();
    void acceptConnection();
	void sendMsg(const std::string & msg, int dest);
	std::string receiveMsg(int rem);
	int NbConnexion();

		// Tests
	std::list<std::string> receptionBuffer;
	std::list<std::string> tranmissionBuffer;

private :
    int nb_client;
    int mainSocket;
	int clientSocket1;
	int clientSocket2;
	int connected = 0;
	struct sockaddr_in loc_addr = { 0 } ;
	struct sockaddr_in client1_addr = { 0 };
	struct sockaddr_in client2_addr = { 0 };
	socklen_t opt1 = sizeof(client1_addr);
	socklen_t opt2 = sizeof(client2_addr);
};
#endif // WIFI_H
