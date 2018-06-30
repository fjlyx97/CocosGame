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
    void resetServer();
    static void sendGameMsg();
    void disconnectClient(Ref* pdata);
    static void recvGameMsg(ODSocket* clientSocket , int clientId);

private:
    ODSocket* mSocket;
    int currentId;
    std::vector<ODSocket*> connectSocket;
    char ip[101];
    int port;
};
#endif