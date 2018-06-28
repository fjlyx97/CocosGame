#ifndef _EnemyManager_H_
#define _EnemyManager_H_
#include "cocos2d.h"
#include "EnemyTank.h"
#include "Vector"
USING_NS_CC;
#define maxEnemyTankNum 10
class EnemyTankManager : public Node
{
public:
    CREATE_FUNC(EnemyTankManager);
    virtual bool init();

    virtual void update(float dt)       //重写update函数
private:
    void createEnemyTank();             //创建敌方坦克对象
        //存放敌方坦克对象列表
    Vector<EnemyTank*> enemyTankArr;
}

#endif