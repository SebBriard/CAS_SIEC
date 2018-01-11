#ifndef WIFI_CL_H
#define WIFI_CL_H

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

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


class WiFiClient
{
public :
    WiFiClient() ;
    ~WiFiClient();
    void Connecting() ;
    void sendMsg(const std::string & msg);
	std::string receiveMsg();
	int is_connected() ;

			// Tests
	std::list<std::string> receptionBuffer;
	std::list<std::string> tranmissionBuffer;
private :
    SOCKET clientSocket;
    int connected = 0 ;
    SOCKADDR_IN serv_addr = { 0 } ;
};

#endif //
