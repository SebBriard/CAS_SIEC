#include "wifi_serv.h"
#include <iostream>
#define PORT 1977
#define NB_CLIENT 2

WiFiServer::WiFiServer(){
    if ((mainSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
    {
        perror("socket()");
        exit(errno);
    }
    nb_client = NB_CLIENT ;
    loc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    loc_addr.sin_port = htons(PORT);
    loc_addr.sin_family = AF_INET;

    if ((bind(mainSocket, (struct sockaddr*)&loc_addr, sizeof(loc_addr))) == SOCKET_ERROR )
    {
        perror("bind()");
        exit(errno);
    }

    if (listen(mainSocket, NB_CLIENT) == SOCKET_ERROR) // on ecoute un nbr max de clients
    {
        perror("listen()");
        exit(errno);
    }
}


WiFiServer::~WiFiServer()
{
    close(mainSocket);
    close(clientSocket1);
    close(clientSocket2);
}

void WiFiServer::acceptConnection(){ // prévu pour deux clients, si on est à la premiere co on renseigne client 1

    if (connected==0)
    {
        if ((clientSocket1 = accept(mainSocket,(struct sockaddr *)&client1_addr, &opt1 ))== INVALID_SOCKET)
        {
            perror("accept()");
            exit(errno);
        }
        else
        {
            connected += 1 ;
        }
    }
    else if (connected==1) // on en est au deuxieme appel de l'acceptation, renseignement du client 2
    {
        if ((clientSocket2=accept(mainSocket,(struct sockaddr *)&client2_addr, &opt2 ))== INVALID_SOCKET)
        {
            perror("accept()");
            exit(errno);
        }
        else
        {
            connected += 1 ;
        }
    }
  std::cout << "Connection accepted" << std::endl;
}

void WiFiServer::sendMsg(const std::string & msg, int dest){ // 1,2
  int bytes_send;
  if (dest == 1)
    {
        if((bytes_send = send(clientSocket1, msg.c_str(), msg.size(),0)) < 0)
        {
            perror("send()");
            exit(errno);
            connected -= 1;
        }
        else
        {
            std::cout << "sent" << bytes_send << " bytes" << std::endl ;
        }
    }
  else if (dest == 2)
        if((bytes_send = send(clientSocket2, msg.c_str(), msg.size(), 0)) < 0)
        {
            perror("send()");
            exit(errno);
            connected -= 1;
        }
        else
        {
            std::cout << "sent" << bytes_send << " bytes" << std::endl ;
        }

  }

std::string WiFiServer::receiveMsg(int rem){
  int bytes_read = 0;
  char buf[1024] ;
  if (rem==0){
     if ((bytes_read = read(clientSocket1,buf, sizeof(buf)-1)) < 0)
     {
        perror("read()");
        exit(errno);
     }
     else
     {
         buf[bytes_read] = '\0' ;
     }
  }
  else if (rem==1)
  {
     if ((bytes_read = read(clientSocket2,buf, sizeof(buf)-1)) < 0)
     {
        perror("read()");
        exit(errno);
     }
     else
     {
         buf[bytes_read] = '\0' ;
     }
  }
  return buf;
}

int WiFiServer::NbConnexion()
{
    return connected ;
}
