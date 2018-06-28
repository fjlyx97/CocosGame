#ifndef _APP_PlayScene_H
#define _APP_PlayScene_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Player.h"

using namespace cocos2d::extension;
USING_NS_CC;

class PlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event);

    CREATE_FUNC(PlayScene);
private:
    bool isSingleGame;
    bool isMulGame;
    Player* firstPlayer;
    Player* secondPlayer;
};

#endif
