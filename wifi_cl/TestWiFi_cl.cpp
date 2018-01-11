#include "wifi_cl.h"
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include "CAN_Abstraction.h"

std::mutex mtx;

void reception_cl(WiFiClient *wf)
{
    std::cout << "entree thread" << std::endl ;
    //int i=0 ;
    while (wf->is_connected()/* i < 3*/){
        std::cout << "wait reception" << std::endl ;
        std::string receivedMsg;
        receivedMsg = wf->receiveMsg();
        //On rajoute en fin de file
        wf->receptionBuffer.push_back(receivedMsg);
       // i++ ;
  }
}

void envoi_cl(WiFiClient *wf)
{
    std::string msg;
    std::cin >> msg;
    wf->sendMsg(msg);
  }

int main()
{
  data_paquet_t *data;
  WiFiClient wfClient;
  std::cout << "The WiFi client has been declared " << std::endl;

  //while(wfClient.is_connected() <= 0)
  //{
      wfClient.Connecting() ;
      std::cout << "connected ? " << wfClient.is_connected() << std::endl;
  //}

  //std::thread first (reception_cl, &wfClient);     // spawn new thread that calls foo()
  std::thread second (envoi_cl, &wfClient);  // spawn new thread that calls bar(0)

  // synchronize threads:
  //first.join();                // pauses until first finishes
  second.join();              // pauses until second finishes

  return 0;
}
