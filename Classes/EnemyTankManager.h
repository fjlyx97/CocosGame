#ifndef _EnemyManager_H_
#define _EnemyManager_H_
#include "cocos2d.h"
#include "EnemyTank.h"
#include "vector"
USING_NS_CC;
#define maxEnemyTankNum 5

class EnemyTankManager : public Node
{
public:
    CREATE_FUNC(EnemyTankManager);
    virtual bool init();
    friend class CollisionDetection;

private:
    void createEnemyTank();             //创建敌方坦克对象
        //存放敌方坦克对象列表
    Vector<EnemyTank*> enemyTankArr;
};

#endif