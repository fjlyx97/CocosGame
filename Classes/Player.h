#ifndef _Player_H_
#define _Player_H_

#include "cocos2d.h"
#include "Entity.h"
#include "BulletManager.h"
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
    //设置玩家隐藏初始位置
    void setPlayerHidePos();
    //设置玩家服务器端初始位置
    void setPlayerServerPos();
    //设置玩家初始位置
    void setPlayerPos(Vec2 pos);
    //返回玩家位置
    Vec2 returnPlayerPos();
    //返回玩家角度
    double returnPlayerRotation();
    //获得按键，操纵玩家
    void actionPlayer(EventKeyboard::KeyCode key , bool isMove);
    //移动玩家
    void movePlayer(EventKeyboard::KeyCode key , bool isMove);
    //开启玩家运动定时器
    void update(float dt);
    //获得子弹管理器
    BulletManager* returnBulletManager();
private:
    char* playerBulletStyle;
    //横纵速度
    double playerSpeedX;
    double playerSpeedY;
    double playerRotation;
    double playerX;
    double playerY;
    bool playerIsMove;    //判断键盘按键是否按下
    //管理玩家子弹
    BulletManager* playerBulletManager;
};

#endif