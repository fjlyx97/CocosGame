#ifndef _GameClient_H_
#define _GameClient_H_
#include "cocos2d.h"
#include "ODSocket/ODSocket.h"
#include "EnemyTankManager.h"
#include "PlayerTankManager.h"
#include "BulletManager.h"
USING_NS_CC;

class GameClient : public Ref
{
public:
    GameClient();
    ~GameClient();
    virtual bool init();
    void connectServer();
    CREATE_FUNC(GameClient);
    void resetClient();
    void setClient(char* ip , int port);
    void recvMsg();

    void bindPlayerTankManager(PlayerTankManager* playerTankmanager);
    void bindPlayerBulletManager(BulletManager* playerBulletmanager);
    void bindEnemyTankManager(EnemyTankManager* enemyTankmanager);
    void bindEnemyBulletManager(BulletManager* enemyBulletmanager);


private:
    ODSocket* mSocket;
    char ip[101];
    int port;

    //玩家管理器
    PlayerTankManager* playerTankmanager;
    //敌人管理器
    EnemyTankManager* enemyTankmanager;
    //子弹管理器
    BulletManager* enemyBulletmanager;
    BulletManager* playerBulletmanager;

};
#endif