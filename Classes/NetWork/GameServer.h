#ifndef _GameServer_H_
#define _GameServer_H_
#include "cocos2d.h"
#include "ODSocket/ODSocket.h"
#include <vector>
#include <string>
USING_NS_CC;
class GameServer : public Ref
{
public:
    GameServer();
    ~GameServer();
    virtual bool init();
    CREATE_FUNC(GameServer);
    static void sendGameMsg();
    static void recvGameMsg(ODSocket* clientSocket);

private:
    ODSocket* mSocket;
    std::vector<ODSocket*> connectSocket;
    char ip[101];
    int port;
};
#endif