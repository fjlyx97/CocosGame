#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "Entity.h"
#include "EnemyTankManager.h"
#include "HelloWorldScene.h"
#include "NetWork/GameServer.h"
#include <thread>
USING_NS_CC;

Scene* PlayScene::createScene()
{
    return PlayScene::create();
}

PlayScene::PlayScene()
{
    playerGameServer = NULL;
}

PlayScene::~PlayScene()
{
    if (playerGameServer != NULL)
    {
        delete playerGameServer;
    }
}


bool PlayScene::init()
{
    //场景初始化
    if ( !Scene::init())
    {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background_image = Sprite::create("Q版坦克素材/Tiled/bg0.jpg");
    if (background_image == nullptr)
    {
        return false;
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(background_image);
    }

    //初始化按键监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed,this);
    listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    // 初始化场景
    isSingleGame = false;
    isMulGame = true;
    //创建怪物管理器
    enemyTank = EnemyTankManager::create();
    //创建人物管理器
    playerTank = PlayerTankManager::create();
    //初始化碰撞检测管理器
    collisionDetectionTank = CollisionDetection::create();
    this->addChild(enemyTank,10);
    this->addChild(playerTank,10);
    this->addChild(collisionDetectionTank,10);
    //初始化本地坦克
    playerTank->addNewPlayer();
    //绑定我方坦克
    collisionDetectionTank->bindPlayerTankManager(playerTank);
    //绑定敌方坦克
    collisionDetectionTank->bindEnemyTankManager(enemyTank);

    if (isSingleGame)
    {

    }
    else if (isMulGame)
    {
        std::thread server(PlayScene::serverStart,this->playerGameServer);
        server.detach();
        //开启消息监听
        NotificationCenter::getInstance()->addObserver(
            this,
            callfuncO_selector(PlayScene::recvServer),
            "playerAction",
            NULL);
        //开启玩家连接监听
        NotificationCenter::getInstance()->addObserver(
            this,
            callfuncO_selector(PlayScene::serverAddNewPlayer),
            "addNewPlayer",
            NULL);
    }
    return true;
}

void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event)
{
    this->playerTank->recvKey(keyCode,true,0);
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event)
{
    this->playerTank->recvKey(keyCode,false,0);
}

void PlayScene::serverStart(GameServer* playerGameServer)
{
    playerGameServer = new GameServer();
    playerGameServer->retain();
}
void PlayScene::recvServer(Ref* playerAction)
{
    log("%s",playerAction);
}
void PlayScene::serverAddNewPlayer(Ref* newPlayer)
{
    //playerTank->recvKey(EventKeyboard::KeyCode::KEY_W,true,0);
    //this->playerTank->addNewPlayer();
    log("add begin");
}