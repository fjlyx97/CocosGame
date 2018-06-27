#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "Entity.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
    return PlayScene::create();
}

bool PlayScene::init()
{
    //场景初始化
    if ( !Scene::init())
    {
        return false;
    }

    //获取屏幕大小
  //  auto visibleSize = Director::getInstance()->getVisibleSize();
  // Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //测试
    player1 = Sprite::create("/home/hhl/cocos/CocosGame/Resources/坦克/我方坦克/1Player/1/m1-1-1.png");
    player1->setPosition(100,100);
    this->addChild(player1);
    
    return true;
}