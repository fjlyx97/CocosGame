#ifndef _Player_H_
#define _Player_H_

#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

class Player:public Entity
{
public:
    Player();
    ~Player();
    CREATE_FUNC(Player);
    virtual bool init();
};

#endif