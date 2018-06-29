#include "GameServer.h"
#include <thread>
#include <cstring>

bool GameServer::init()
{
    this->port =  8000;
    log("%d",this->port);
    return true;
}

GameServer::GameServer()
{
    this->mSocket = new ODSocket();
    this->mSocket->Init();
    this->mSocket->Create(AF_INET, SOCK_STREAM , 0);
    this->mSocket->Bind(this->port);
    if (!(this->mSocket->Listen(6)))
    {
        log("监听端口失败");
    }
    while (true)
    {
        ODSocket* clientSocket = new ODSocket;
        if (mSocket->Accept(*clientSocket,ip))
        {
            connectSocket.push_back(clientSocket);
            std::thread recvThread(GameServer::recvGameMsg,clientSocket);
            recvThread.detach();
        }
        //此处似乎有内存泄露
    }
}

void GameServer::recvGameMsg(ODSocket * clientSocket)
{
    char message[1024];
    while (true)
    {
        memset(message,0,sizeof(message));
        clientSocket->Recv(message,1024,0);
        log("%s",message);
    }
}

GameServer::~GameServer()
{
    this->mSocket->Clean();
    for (auto socket : connectSocket)
    {
        delete socket;
    }
}