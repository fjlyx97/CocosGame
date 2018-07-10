#ifndef _GameServer_H_
#define _GameServer_H_
#include "cocos2d.h"
#include "ODSocket/ODSocket.h"
#include <queue>
#include <string>
#include "PlayerTankManager.h"
#include "EnemyTankManager.h"
#include <mutex>
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
    //获得IP和端口
    void setIp(char* ip , int port);
    //往所有服务器玩家发送新玩家坐标广播
    void sendNewPlayerPos(Ref* pos);
    //往玩家发送服务器所有数据
    void sendOldPlayer(Ref* pdata);
    //断线检测
    void disconnectClient(Ref* pdata);
    //循环接受服务端消息
    void recvGameMsg(playerClient* newPlayer);
    //开始接受
    void start();
    //绑定管理器
    void bindEnemyTankManager(EnemyTankManager* enemyTankmanager);
    void bindPlayerTankManager(PlayerTankManager* playerTankmanager);
    void bindMsgQueue(std::queue<int>* MsgQueue);

private:
    ODSocket* mSocket;
    int currentId;
    int bookId[6];
    std::vector<playerClient*> connectSocket;
    char ip[101];
    int port;
    //敌人管理器
    EnemyTankManager* enemyTankmanager;
    //玩家管理器
    PlayerTankManager* playerTankmanager;
    //消息队列
    std::queue<int>* MsgQueue;
    std::mutex mutexMsg;
};
#endif