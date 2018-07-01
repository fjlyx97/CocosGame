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
    //增加观察者，接收玩家连接服务器I
    
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
    gameClientSocket->connectServer();
}