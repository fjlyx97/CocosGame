#include "EnemyTankManager.h"
#include ""  //玩家
#include "EnemyTank.h"

bool EnemyTankManager::init()
{
    createEnemyTank();          //创建敌方坦克缓存
    this->scheduleUpdate();     //开启uodate函数调用
    return true;
}

void EnemyTankManager::createEnemyTank()
{
    EnemyTank* enemyTank = NULL;
    Sprite* sprite = NULL;

    for(int i=0;i<maxEnemyTankNum;i++)
    {
        //创建敌方坦克对象
        enemyTank = EnemyTank::create();
        enemyTank->bindSprite(Sprite::create("Q版坦克素材/enemy/canon17.png"));
        enemyTank->reset();

        //添加敌方坦克对象
        this->addChild(enemyTank);
        
        //保存敌方坦克对象到列表
        enemyTankArr.pushBack(enemyTank);
    }
}

void EnemyTankManager::update(float dt)
{
}