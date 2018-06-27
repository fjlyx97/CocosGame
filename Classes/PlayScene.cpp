#include "PlayScene.h"
#include "SimpleAudioEngine.h"

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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background_image = Sprite::create("/home/hhl/cocos/CocosGame/Resources/Q版坦克素材/bg_new.jpg");
    if (background_image == nullptr)
    {
        return false;
     
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        //background_image->setScale(20);
        this->addChild(background_image);
    }



    
    return true;
}