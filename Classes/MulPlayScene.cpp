#include "SimpleAudioEngine.h"
#include "Entity.h"
#include "EnemyTankManager.h"
#include "HelloWorldScene.h"
#include "NetWork/GameServer.h"
#include "MulPlayScene.h"
#include <thread>
USING_NS_CC;

MulPlayScene::MulPlayScene()
{

}

MulPlayScene::~MulPlayScene()
{
    if (playerGameServer != NULL)
    {
        delete playerGameServer;
    }
}


bool MulPlayScene::init()
{
    if ( !Scene::init())
    {
        return false;
    }
    log("开启监听");
    //初始化游戏背景
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background_image = Sprite::create("Q版坦克素材/Tiled/bg4.jpg");
    if (background_image == nullptr)
    {
        return false;
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(background_image);
    }

    std::thread server(MulPlayScene::serverStart,this->playerGameServer);
    server.detach();
    //开启消息监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::recvServer),
        "playerAction",
        NULL);
    //开启玩家连接监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::serverAddNewPlayer),
        "addNewPlayer",
        NULL);

    return true;
}

void MulPlayScene::serverStart(GameServer* playerGameServer)
{
    playerGameServer = new GameServer();
    playerGameServer->retain();
}
void MulPlayScene::recvServer(Ref* playerAction)
{
    log("%s",playerAction);
}
void MulPlayScene::serverAddNewPlayer(Ref* newPlayer)
{
    //playerTank->recvKey(EventKeyboard::KeyCode::KEY_W,true,0);
    //this->playerTank->addNewPlayer();
}