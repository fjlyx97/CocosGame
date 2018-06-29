#include "GameServer.h"

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
    //this->mSocket->Bind(port);
    if (this->mSocket->Listen(6))
    {

    }
}

GameServer::~GameServer()
{
    this->mSocket->Clean();
}