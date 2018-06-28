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
    //设置玩家大小
    void setPlayerScale(float scale);
    //设置玩家速度
    void setPlayerSpeed(float speedX ,float speedY);
    //设置玩家初始位置
    void setPlayerPos(Vec2 pos);
    //返回玩家位置
    Vec2 returnPlayerPos();
    //移动玩家
    void movePlayer(EventKeyboard::KeyCode key , bool isMove);
    //开启玩家运动定时器
    void update(float dt);
private:
    //横纵速度
    double playerSpeedX;
    double playerSpeedY;
    double playerX;
    double playerY;
    bool playerIsMove;    //判断键盘按键是否按下
};

#endif