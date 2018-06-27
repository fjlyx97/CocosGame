#ifndef _GameServer_H_
#define _GameServer_H_
#include "ODSocket/ODSocket.h"
#include <string>
class GameServer
{
public:
    GameServer(std::string ip ,int port);
    ~GameServer();

private:
    ODSocket mSocket;
    std::string ip;
    int port;
};
#endif