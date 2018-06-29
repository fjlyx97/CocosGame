#ifndef _FSM_H_
#define _FSM_H_
#include "cocos2d.h"
USING_NS_CC;

enum EnumState
{
    crashWall,
    forward,
    changeDirection,
};

class TankState : public Node
{
public:
    CREATE_FUNC(TankState);
    virtual bool init();
    EnumState enCurState;       //当前状态

    bool CrashWall();       //判断是否撞墙

    void toForward();
    void toCrashWall();
    void toChangeDirection();     //改变方向  

    void changeState(EnumState enState);    //切换状态

    virtual void update(float dt);

};
#endif