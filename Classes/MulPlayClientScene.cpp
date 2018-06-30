#include "MulPlayClientScene.h"

USING_NS_CC;

Scene* MulPlayClientScene::createScene()
{
    return MulPlayClientScene::create();
}

MulPlayClientScene::MulPlayClientScene()
{

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


    return true;
}