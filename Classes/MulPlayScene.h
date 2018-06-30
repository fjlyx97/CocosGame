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

using namespace cocos2d::extension;
USING_NS_CC;

class MulPlayScene : public Scene
{
public:
    static cocos2d::Scene* createScene();
    MulPlayScene();
    ~MulPlayScene();
    virtual bool init();

    //开始服务器
    static void serverStart(GameServer* playerGameServer);
    //接受服务器消息
    void recvServer(Ref* playerAction);
    void serverAddNewPlayer(Ref* newPlayer);

    //网络管理器
    GameServer* playerGameServer;

    CREATE_FUNC(MulPlayScene);

};
#endif