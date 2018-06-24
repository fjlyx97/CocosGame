#ifndef _APP_PlayScene_H
#define _APP_PlayScene_H
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d::extension;
USING_NS_CC;

class PlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
private:
    Sprite* player1;
};

#endif