#ifndef _MulPlayClientScene_H_
#define _MulPlayClientScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
using namespace cocos2d::extension;

class MulPlayClientScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    MulPlayClientScene();
    ~MulPlayClientScene();

    virtual bool init();


    CREATE_FUNC(MulPlayClientScene);
};
#endif