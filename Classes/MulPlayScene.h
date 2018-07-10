#ifndef _MulPlayScene_H_
#define _MulPlayScene_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Player.h"
#include "Entity.h"
#include "EnemyTankManager.h"
#include "PlayerTankManager.h"
#include "CollisionDetection.h"
#include "NetWork/GameServer.h"
#include <vector>

using namespace cocos2d::extension;
USING_NS_CC;

class MulPlayScene : public Scene
{
public:
    static cocos2d::Scene* createScene();
    MulPlayScene();
    ~MulPlayScene();
    virtual bool init();

    //发送坐标
    void sendPosition();
    //开始服务器
    void serverStart(GameServer* playerGameServer, char* ip , int port);
    //接受服务器消息
    void recvServer(Ref* playerAction);
    void serverAddNewPlayer(Ref* newPlayer);
    void serverDeletePlayer(Ref* delPlayer);
    void sendIp(Ref* ipData);

    //不断发送服务器信息
    void update(float dt);
    //玩家子弹管理器
    BulletManager* playerBulletmanager;
    //敌人子弹管理器
    BulletManager* enemyBulletmanager;
    //敌人管理器
    EnemyTankManager* enemyTankmanager;
    //玩家管理器
    PlayerTankManager* playerTankmanager;
    //碰撞管理器
    CollisionDetection* collisionDetectionTank;
    //网络管理器
    GameServer* playerGameServer;

    void onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event);

    CREATE_FUNC(MulPlayScene);
private:
    int playerNum;
    int bookPlayer[6];
    char ip[101];
    int port;
    std::mutex updateMutex;
    std::queue<int> MsgQueue;
	float temp_x, temp_y;


};
#endif