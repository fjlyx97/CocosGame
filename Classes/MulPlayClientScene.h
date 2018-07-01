#ifndef _MulPlayClientScene_H_
#define _MulPlayClientScene_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "NetWork/GameClient.h"
#include "PlayerTankManager.h"


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
    void updataGameInfo(Ref* updateInfo);

    virtual bool init();
    CREATE_FUNC(MulPlayClientScene);


private:
    char ip[101];
    int port;
    GameClient* gameClientSocket;
    //玩家管理器
    PlayerTankManager* playerTankmanager;

};
#endif