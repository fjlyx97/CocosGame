#include "GameServer.h"
GameServer::GameServer()
{
    this->mSocket.Init();
}

GameServer::~GameServer()
{
    this->mSocket.Clean();
}