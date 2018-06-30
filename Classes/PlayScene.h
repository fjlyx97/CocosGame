#ifndef _APP_PlayScene_H
#define _APP_PlayScene_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Player.h"
#include "Entity.h"
#include "EnemyTankManager.h"
#include "PlayerTankManager.h"
#include "CollisionDetection.h"
#include "NetWork/GameServer.h"

using namespace cocos2d::extension;
USING_NS_CC;

class PlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    PlayScene();
    ~PlayScene();

    virtual bool init();
    
    void onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event);
    //开始服务器
    static void serverStart(GameServer* playerGameServer);
    //接受服务器消息
    void recvServer(Ref* playerAction);
    void serverAddNewPlayer(Ref* newPlayer);

    CREATE_FUNC(PlayScene);
private:
    bool isSingleGame;
    bool isMulGame;
    //敌人管理器
    EnemyTankManager* enemyTank;
    //玩家管理器
    PlayerTankManager* playerTank;
    //碰撞管理器
    CollisionDetection* collisionDetectionTank;
    //网络管理器
    GameServer* playerGameServer;
};

#endif
