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

    //获得是否存活状态
    bool isAlive();

    virtual bool init();
    CREATE_FUNC(EnemyTank);

private:
    bool enemyIsAlive;
    char enemyDir; //判断当前坦克对准的方向，wsad分别对应
};

#endif