#include "GameServer.h"
GameServer::GameServer(std::string ip , int port) : ip(ip) , port(port)
{
    this->mSocket.Init();
    this->mSocket.Create(AF_INET, SOCK_STREAM , 0);
}

GameServer::~GameServer()
{
    this->mSocket.Clean();
}