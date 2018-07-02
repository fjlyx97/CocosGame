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


    //创建人物管理器
    playerTankmanager = PlayerTankManager::create();
    //创建怪物管理器
    enemyTankmanager = EnemyTankManager::create();
    //创建子弹管理器
    playerBulletManager = BulletManager::create();
    enemyBulletManager = BulletManager::create();

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
        enemyBulletManager->addNewBullet(0,-1,-1,"Q版坦克素材/bullet/bullet5.png",false);
        playerBulletManager->addNewBullet(0,-1,-1,"Q版坦克素材/bullet/bullet7.png",false);
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


