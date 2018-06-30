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
    this->playerNum = 0;
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
    //创建怪物管理器
    enemyTankmanager = EnemyTankManager::create();
    //创建人物管理器
    playerTankmanager = PlayerTankManager::create();
    //初始化碰撞检测管理器
    collisionDetectionTank = CollisionDetection::create();
    collisionDetectionTank->bindEnemyTankManager(enemyTankmanager);
    collisionDetectionTank->bindPlayerTankManager(playerTankmanager);
    this->addChild(enemyTankmanager,10);
    this->addChild(playerTankmanager,10);
    this->addChild(collisionDetectionTank,10);
    //初始化服务器端玩家坦克
    for (int i = 1 ; i <= 6 ; i++)
    {
        playerTankmanager->addNewPlayer();
    }
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        player->setPlayerHidePos();
    }

    std::thread server(MulPlayScene::serverStart,this->playerGameServer);
    server.detach();
    //开启玩家消息监听
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
    //开启玩家断线监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::serverDeletePlayer),
        "playerDisconnect",
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
    int index = 0;
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        if (index == playerNum)
        {
            player->setPlayerServerPos();
            break;
        }
        index++;
    }
    this->playerNum++;
}

void MulPlayScene::serverDeletePlayer(Ref* delPlayer)
{
    int playerId = atoi((char*)delPlayer);
    int index = 0;
    for (auto player : this->playerTankmanager->returnPlayerTankManager())
    {
        if (index == playerId)
        {
            player->removeFromParent();
            playerTankmanager->returnPlayerTankManager().eraseObject(player);
            break;
        }
        index++;
    }
}