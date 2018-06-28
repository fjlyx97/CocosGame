#ifndef _EnemyTank_H_
#define _EnemyTank_H_
#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

class EnemyTank : public Entity
{
public:
    EnemyTank();
    ~EnemyTank();
    void show();    //显示敌方坦克
    void hide();    //隐藏敌方坦克
    void reset();   //重置坦克数据
    bool isAlive(); //获得是否存活状态

    virtual bool init();
    CREATE_FUNC(EnemyTank);

private:
    bool enemyIsAlive;
    char enemyDir; //判断当前坦克对准的方向，wsad分别对应
};

#endif