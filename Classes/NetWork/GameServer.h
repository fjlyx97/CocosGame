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
    //服务器初始化
    void resetServer();
    //往所有服务器玩家发送新玩家坐标广播
    void sendNewPlayerPos(Ref* pos);
    //往新玩家发送服务器所有数据
    void sendOldPlayer(Ref* pdata);
    //往所有服务器发送广播
    void sendGameMsg(Ref* pdata);
    //断线检测
    void disconnectClient(Ref* pdata);
    //循环接受服务端消息
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