#ifndef _MulPlayClientScene_H_
#define _MulPlayClientScene_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "NetWork/GameClient.h"
#include "PlayerTankManager.h"
#include "EnemyTankManager.h"
#include "BulletManager.h"
#include "EnemyTank.h"
#include "Player.h"
#include "MulPlayClientScene.h"
#include "BulletManager.h"

USING_NS_CC;
using namespace cocos2d::extension;

class MulPlayClientScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    MulPlayClientScene();
    ~MulPlayClientScene();
    void getConnectIp(Ref* pIpdata);
    void createClient();
    void sendKeyMsg(EventKeyboard::KeyCode keyCode , bool isPress);
    void setClientID(Ref* pdata);

    //void bindClient(MulPlayerClientScene* client);

    //开启客户端按键监听
    void onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event);

    virtual bool init();
    CREATE_FUNC(MulPlayClientScene);


private:
    char ip[101];
    int port;
    int clientId;
    GameClient* gameClientSocket;
    //玩家管理器
    PlayerTankManager* playerTankmanager;
    //敌人管理器
    EnemyTankManager* enemyTankmanager;
    //子弹管理器
    BulletManager* enemyBulletManager;
    BulletManager* playerBulletManager;

};
#endif