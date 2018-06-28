#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "EnemyTankManager.h"

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

    auto background_image = Sprite::create("Q版坦克素材/Tiled/bg0.jpg");
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


    
    //键盘事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed,this);
    //listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased,this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    //坦克创建
    auto tank = Sprite::create("Q版坦克素材/plane1.png");
    tank->setTag(1);
    tank->setPosition(Point(50,50));
    tank->setScale(0.2);
    this->addChild(tank,10);

    EnemyTankManager* enemyTank = EnemyTankManager::create();
    this->addChild(enemyTank,10);

    return true;
}

//控制坦克移动
void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event)
{

    auto tank = getChildByTag(1);
    if(keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        auto moveForward = MoveBy::create(1,Point(0,5));
        RepeatForever* repeatForward = RepeatForever::create(moveForward);
        tank->runAction(repeatForward);

    }
    if(keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        auto moveBackward = MoveBy::create(1,Point(0,-5));
        RepeatForever* repeatBackward = RepeatForever::create(moveBackward);
        tank->runAction(repeatBackward);
    }
    if(keyCode == EventKeyboard::KeyCode::KEY_A )
    {
        auto moveLeft = MoveBy::create(1,Point(-5,0));
        RepeatForever* repeatLeft = RepeatForever::create(moveLeft);
        tank->runAction(repeatLeft);
    }
    if(keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        auto moveRight = MoveBy::create(1,Point(5,0));
        RepeatForever* repeatRight = RepeatForever::create(moveRight);
        tank->runAction(repeatRight);
    }
}
