#ifndef _EnemyTank_H_
#define _EnemyTank_H_
#include "cocos2d.h"
#include "Entity.h"
#include "BulletManager.h"
USING_NS_CC;

class EnemyTank : public Entity
{
public:
    EnemyTank();
    ~EnemyTank();
    virtual bool init();    
    CREATE_FUNC(EnemyTank);

    //坦克位置随机重置
    void reset();   
    //获得是否活动状态
    void isAlive();
    //设置大小
    void setEnemyScale(float scale);
    //设置速度
    void setEnemySpeed(float speedX ,float speedY);
    //设置隐藏初始位置
    void setEnemyHidePos();
    //设置玩家转向
    void setEnemyRotation(double rotation);
    //设置服务器端初始位置
    //void setEnemyServerPos();
    //设置初始位置
    void setEnemyPos(Vec2 pos);
    //返回位置
    Vec2 returnEnemyPos();
    //返回玩家方向
    double returnEnemyTankRotation();
    void TankAI(float dt);
    friend class CollisionDetection;
    BulletManager* returnBulletManager();
    //返回敌机爆炸动画
    Animate* boomAnimate();

private:
    char* enemyTankBulletStyle;
    double enemyspeedX;
    double enemyspeedY;
    double enemyRotation;
    bool enemyIsAlive;
    double enemyPositionX;
    double enemyPositionY;
    //获得子弹管理器
    BulletManager*  enemyBulletManager;
};

#endif