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

    
    return true;
}