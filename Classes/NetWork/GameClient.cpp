#include "GameClient.h"
#include <cstring>

GameClient::GameClient()
{
    resetClient();
    this->mSocket = new ODSocket;
    this->mSocket->Init();
    this->mSocket->Create(AF_INET, SOCK_STREAM , 0);
}

GameClient::~GameClient()
{
    delete this->mSocket;
}

bool GameClient::init()
{
    return true;
}

void GameClient::resetClient()
{
    this->port = 8000;
    strcpy(ip,"127.0.0.1");
}

void GameClient::connectServer()
{
    log("%s",this->ip);
    log("%d",this->port);
    bool result = this->mSocket->Connect("127.0.0.1",8000);
    int retryTimes = 0;
    while (result == false && retryTimes < 7)
    {
        log("retry connecting...");
        result = mSocket->Connect(ip, port);
        retryTimes++;
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            Sleep(500);
        #else
            usleep(500);
        #endif
    }

    
    if (result)
    {

    }
}

void GameClient::setClient(char* ip , int port)
{
    strcpy(this->ip,ip);
    this->port = port;
}