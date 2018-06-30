#ifndef _GameServer_H_
#define _GameServer_H_
#include "cocos2d.h"
#include "ODSocket/ODSocket.h"
#include <vector>
#include <string>
USING_NS_CC;
struct playerClient
{
    ODSocket* connectSocket;
    int id;
    playerClient(ODSocket* s , int clientId)
    {
        connectSocket = s;
        id = clientId;
    }
};
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
    static void recvGameMsg(playerClient* newPlayer);

private:
    ODSocket* mSocket;
    int currentId;
    int bookId[6];
    std::vector<playerClient*> connectSocket;
    char ip[101];
    int port;
};
#endif