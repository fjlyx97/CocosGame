#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
    this->enemyIsAlive = false;
}
EnemyTank::~EnemyTank()
{
}

bool EnemyTank::init()
{
    return true;
}

void EnemyTank::show()
{
    if(getSprite() != NULL)
    {
        setVisible(true);
        enemyIsAlive = true;
    }
}

void EnemyTank::hide()
{
    if(getSprite() != NULL)
    {
        setVisible(false);    //设置不可见
        reset();                //重置敌方坦克数据
        enemyIsAlive = false;   //标记坦克为非活动状态（隐藏状态）
    }
}

void EnemyTank::reset()
{
    if(getSprite() != NULL)
    {
        setPosition(Point(800 + CCRANDOM_0_1() * 2000,200 - CCRANDOM_0_1() * 100));
    }
}

bool EnemyTank::isAlive()
{
    return this->enemyIsAlive;
}