#include "wifi_cl.h"
#include <iostream>
#define PORT 1977

WiFiClient::WiFiClient(){
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.1");
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_family = AF_INET;
}



void WiFiClient::Connecting()
{
    if (connect(clientSocket, (SOCKADDR *)&serv_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }
    else
    {
        connected = 1 ;
    }
}

void WiFiClient::sendMsg(const std::string & msg){
  int bytes_send;
  bytes_send = send(clientSocket, msg.c_str(), msg.size(), 0);
  if (bytes_send < 0){
    perror("send()");
    exit(errno);
    connected -= 1;
  }
  std::cout << bytes_send << " bytes have been sent"<< std::endl;
}

std::string WiFiClient::receiveMsg(){
  int bytes_read;
  char buf[1024] ;
  bytes_read = recv(clientSocket, buf, sizeof buf - 1,0) ;
  if (bytes_read < 0)
  {
      perror("recv()");
      exit(errno);
  }
  else
  {
      buf[bytes_read] = '\0' ;
  }
  std::cout << "buffer : " << buf << std::endl;
  return buf;
}

int WiFiClient::is_connected()
{
    return connected ;
}

WiFiClient::~WiFiClient()
{
    close(clientSocket);
}
