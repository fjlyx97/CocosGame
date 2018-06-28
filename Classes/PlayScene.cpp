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
    if (isSingleGame)
    {

    }
    else if (isMulGame)
    {
        //初始化我方坦克
        firstPlayer = Player::create();
        secondPlayer = Player::create();
        firstPlayer->bindSprite(Sprite::create("Q版坦克素材/plane1.png"));
        secondPlayer->bindSprite(Sprite::create("Q版坦克素材/plane2.png"));

        firstPlayer->setPosition(200,100);
        firstPlayer->setPlayerScale(0.2);
        firstPlayer->setPlayerPos(firstPlayer->getPosition());
        secondPlayer->setPosition(300,100);
        secondPlayer->setPlayerScale(0.2);
        secondPlayer->setPlayerPos(secondPlayer->getPosition());

        this->addChild(firstPlayer);
        this->addChild(secondPlayer);
    }

    return true;
}
void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event)
{
    firstPlayer->movePlayer(keyCode,true);
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event)
{
    firstPlayer->movePlayer(keyCode,false);
}