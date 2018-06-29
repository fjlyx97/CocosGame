#include "FSM.h"

bool TankState::init()
{
    this->scheduleUpdate();
    return true;
}

void TankState::changeState(EnumState enState)  //改变状态
{
    this->enCurState = enState;
}

bool TankState::CrashWall()             //判断是否撞墙
{
    float ran = CCRANDOM_0_1();
    if(ran < 0.1f)
    {
        return true;
    }
    return false;
}


void TankState::toForward()           //改变方向
{
    log("forward.");
}
void TankState::toCrashWall()           //改变方向
{
    log("crashWall.");
}
void TankState::toChangeDirection()           //改变方向
{
    log("changeDirection.");
}

void TankState::update(float dt)
{
    switch(enCurState)
    {
        case crashWall: 
            toChangeDirection();  
            changeState(changeDirection); 
            break;
        case changeDirection:
            toForward();
            changeState(forward);
            break;
        case forward:
            if(CrashWall())
            {
                toCrashWall();
                changeState(crashWall);
            }
            else
            {
                toForward();
            }
            break;
    }
    
        
}