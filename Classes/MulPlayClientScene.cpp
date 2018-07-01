#include "MulPlayClientScene.h"
#include <thread>

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
    strcmp(this->ip,pIpData);
    std::thread temp = std::thread(&MulPlayClientScene::createClient,this);
    temp.detach();
}
void MulPlayClientScene::createClient()
{
    log("成功运行");
}
