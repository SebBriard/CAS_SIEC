#include "wifi_serv.h"
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include "CAN_Abstraction.h"

std::mutex mtx;

void reception_cl1(WiFiServer *wf)
{
  //while (wf->NbConnexion()> 0){
    std::string receivedMsg = {0};
    std::cout << "attente message " << std::endl;

    receivedMsg = wf->receiveMsg(0);
    std::cout << "Message received: " << receivedMsg  << std::endl;
    //On rajoute en fin de file
    wf->receptionBuffer.push_back(receivedMsg);
    //}
}

void reception_cl2(WiFiServer *wf)
{
  //while (wf->NbConnexion()> 0){
    std::string receivedMsg= {0};
    std::cout << "attente message " << std::endl;

    receivedMsg = wf->receiveMsg(1);
    std::cout << "Message received: " << receivedMsg  << std::endl;
    //On rajoute en fin de file
    wf->receptionBuffer.push_back(receivedMsg);
  //}
}

void envoi(WiFiServer *wf)
{
    std::cout << "entree thread" << std::endl ;
    std::string msg;
    std::cin >> msg;
    wf->sendMsg(msg,1);
    if (wf->NbConnexion()== 2)
    {
        wf->sendMsg(msg,2);
    }
}

int main()
{
  data_paquet_t *data;
  WiFiServer wfServer;
  std::cout << "The WiFi server has been declared" << std::endl;


  wfServer.acceptConnection();
  int nb_co = 0 ;
  if ((nb_co = wfServer.NbConnexion()) > 0 )
  {
        std::cout << nb_co << " connections have been accepted" << std::endl;

        std::thread first (reception_cl1, &wfServer);     // spawn new thread that calls foo()
        //std::thread second (envoi, &wfServer);  // spawn new thread that calls bar(0)

        // synchronize threads:
        first.join();                // pauses until first finishes
        //second.join();              // pauses until second finishes
  }
   wfServer.acceptConnection();
    if ((nb_co = wfServer.NbConnexion()) == 2 )
  {
        std::cout << nb_co << " connections have been accepted" << std::endl;
        std::thread third (reception_cl2, &wfServer);     // spawn new thread that calls foo()
        third.join() ;
  }
  return 0;
}
