#include "MulPlayClientScene.h"
#include <thread>
#include <ODSocket/ODSocket.h>

USING_NS_CC;

Scene* MulPlayClientScene::createScene()
{
    return MulPlayClientScene::create();
}

MulPlayClientScene::MulPlayClientScene()
{
    //初始化连接服务端
    //this->addChild(this->connectClient);
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayClientScene::getConnectIp),
        "sendIp",
        NULL);
    //设置客户端id
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayClientScene::setClientID),
        "sendClientId",
        NULL);
}

MulPlayClientScene::~MulPlayClientScene()
{
}

bool MulPlayClientScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background_image = Sprite::create("QTank/Tiled/bg4.jpg");
    if (background_image == nullptr)
    {
        return false;
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(background_image);
    }


    //创建人物管理器
    playerTankmanager = PlayerTankManager::create();
    //创建怪物管理器
    enemyTankmanager = EnemyTankManager::create();
    //创建子弹管理器
    playerBulletManager = BulletManager::create();
    enemyBulletManager = BulletManager::create();
    //开启客户端按键监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MulPlayClientScene::onKeyPressed,this);
    listener->onKeyReleased = CC_CALLBACK_2(MulPlayClientScene::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    this->addChild(playerTankmanager,10);
    this->addChild(enemyTankmanager,10);
    this->addChild(playerBulletManager,10);
    this->addChild(enemyBulletManager,10);
    //初始化客户端坦克
    for (int i = 1 ; i <= 6 ; i++)
    {
        playerTankmanager->addNewPlayer();
    }
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        player->setPlayerHidePos();
    }
    //初始化子弹
    for (int i = 1 ; i <= 50 ; i++)
    {
        enemyBulletManager->addNewBullet(0,-1,-1,"QTank/bullet/bullet5.png",false);
        playerBulletManager->addNewBullet(0,-1,-1,"QTank/bullet/bullet7.png",false);
    }

    return true;
}
void MulPlayClientScene::getConnectIp(Ref* pIpData)
{
    log("%s",pIpData);
    char* ipInfo = (char*)pIpData;
    int i;
    for (i = 0 ; i < strlen(ipInfo) ; i++)
    {
        if (ipInfo[i] != ' ')
        {
            this->ip[i]  = ipInfo[i];
        }
        else
        {
            this->ip[i] = '\0';
            break;
        }
    }
    this->port = 8000;
    std::thread client = std::thread(&MulPlayClientScene::createClient,this);
    client.detach();
}
void MulPlayClientScene::createClient()
{
    log("成功运行");
    gameClientSocket = new GameClient();
    gameClientSocket->retain();
    gameClientSocket->setClient(this->ip,this->port);
    gameClientSocket->bindPlayerTankManager(this->playerTankmanager);
    gameClientSocket->bindEnemyTankManager(this->enemyTankmanager);
    gameClientSocket->bindEnemyBulletManager(this->enemyBulletManager);
    gameClientSocket->bindPlayerBulletManager(this->playerBulletManager);
    //gameClientSocket->bindClient(this);
    gameClientSocket->connectServer();
}


void MulPlayClientScene::onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event)
{
    this->sendKeyMsg(keyCode,true);
}

void MulPlayClientScene::onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event)
{
    this->sendKeyMsg(keyCode,false);
}

void MulPlayClientScene::sendKeyMsg(EventKeyboard::KeyCode keyCode , bool isPress)
{
    std::string clientMsg = Value(this->clientId).asString();
    if (isPress)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_W)
        {
            clientMsg += "playerUp";
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S)
        {
            clientMsg += "playerDown";
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_A)
        {
            clientMsg += "playerLeft";
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            clientMsg += "playerRight";
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_J)
        {
            clientMsg += "playerAttack";
        }
    }
    else
    {
        clientMsg += "playerStop";
    }
    //log("进入事件");
    NotificationCenter::getInstance()->postNotification("sendMsg",(Ref*)((char*)clientMsg.data()));
}

void MulPlayClientScene::setClientID(Ref* pdata)
{
    this->clientId = atoi((char*)pdata);
}