#include "GameClient.h"
#include <cstring>
#include <thread>

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
    std::thread recvMsg = std::thread(&GameClient::recvMsg,this);
    recvMsg.detach();
}

void GameClient::setClient(char* ip , int port)
{
    strcpy(this->ip,ip);
    this->port = port;
}

void GameClient::recvMsg()
{
    while(true)
    {
        char recvData[50];
        memset(recvData,0,sizeof(recvData));
        this->mSocket->Recv(recvData,3,0);
        int max_size = atoi(recvData);
        memset(recvData,0,sizeof(recvData));
        this->mSocket->Recv(recvData,max_size,0);
        //将接受到的字符串发送出去处理
        //log("%s",recvData);
        NotificationCenter::getInstance()->postNotification("sendContent",(Ref*)recvData);
    }
}