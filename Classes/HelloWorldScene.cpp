/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 问题日志
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 场景初始化
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //关闭按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));

    //创建菜单
    auto singleBeginGame = Label::createWithTTF("SinglePlayer Game", "fonts/Marker Felt.ttf", 20);
    //singleBeginGame->setColor(Color3B(0,255,0));
    singleBeginGame->setTag(1);
    auto singleBeginGameItem = MenuItemLabel::create(singleBeginGame,CC_CALLBACK_0(HelloWorld::menuSingleBeginGame,this));

    auto multiBeginGame= Label::createWithTTF("MultiPlayer Game", "fonts/Marker Felt.ttf", 20);
    multiBeginGame->setTag(2);
    //multiBeginGame->setColor(Color3B(0,255,0));
    auto multiBeginGameItem = MenuItemLabel::create(multiBeginGame,CC_CALLBACK_0(HelloWorld::menuMultiBeginGame,this));

    auto exitGame = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 20);
    exitGame->setColor(Color3B(0,255,0));
    auto exitGameItem = MenuItemLabel::create(exitGame,CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));

    auto menu = Menu::create(singleBeginGameItem,multiBeginGameItem,exitGameItem ,NULL);
    menu->alignItemsVerticallyWithPadding(10);
    menu->setPosition(visibleSize.width/2 , visibleSize.height/2);
    this->addChild(menu, 1);


    //初始化场景
    auto label = Label::createWithTTF("Tank War Multiplayer", "fonts/Marker Felt.ttf", 24);
    label->setTag(10);


    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 将文字放置中央
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    auto background_image = Sprite::create("Q版坦克素材/bg_new.jpg");
    if (background_image == nullptr)
    {
        problemLoading("场景加载失败");
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(background_image);
    }
    //测试事件监听
    // a 124 s 142 d 127 w 146
    //auto listener = EventListenerKeyboard::create();
    //listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode , Event* event){
    //    log("%d %c",keyCode,keyCode);
    //};
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //按钮回调函数
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::menuSingleBeginGame()
{
    problemLoading("Single Play Game");
    auto singleBeginGameScene = PlayScene::create();
    Director::getInstance()->replaceScene(singleBeginGameScene);
}

void HelloWorld::menuMultiBeginGame()
{
    problemLoading("Multi Play Game");

    //输入框--创建连接
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto netWorking = Sprite::create("Q版坦克素材/bg_frame.png");
    netWorking->setPosition(Point((visibleSize.width/2)+20,visibleSize.height/2));    
    this->addChild(netWorking,4);

    auto ipContent = Scale9Sprite::create("Q版坦克素材/exchange/exchange_num.png");
    auto ipEditBox = EditBox::create(Size(300,50),ipContent);
    ipEditBox->setPosition(Vec2(visibleSize.width/2+20,visibleSize.height/2+40));
    ipEditBox->setText("请输入IP地址"); //初始化文字
    ipEditBox->setFontSize(20);   //文字的大小：注意！！！  这个设置没有任何效果。这也是为什么要自己建立背景的一个问题

    auto portContent = Scale9Sprite::create("Q版坦克素材/exchange/exchange_num.png");
    auto portEditBox = EditBox::create(Size(300,50),portContent);
    portEditBox->setPosition(Vec2(visibleSize.width/2+20,visibleSize.height/2-40));
    portEditBox->setText("请输入端口号"); //初始化文字
    portEditBox->setFontSize(20);   //文字的大小：注意！！！  这个设置没有任何效果。这也是为什么要自己建立背景的一个问题

    this->addChild(ipEditBox,5);
    this->addChild(portEditBox,5);
    log("%s",ipEditBox->getText());
    log("%s",portEditBox->getText());
}
