#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
    speed = 2;
    this->enemyIsAlive = false;
}
EnemyTank::~EnemyTank()
{
}

bool EnemyTank::init()
{
    this->scheduleUpdate();
    return true;
}

void EnemyTank::show()
{
    if(getSprite() != NULL)
    {
        setVisible(true);       //设置可见
        enemyIsAlive = true;    //标记坦克为活动状态
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
        setPosition(Vec2(CCRANDOM_0_1()*400,CCRANDOM_0_1()*200));
    }
}

bool EnemyTank::isAlive()
{
    return this->enemyIsAlive;
}

void EnemyTank::update(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if(this->getPositionX() < (visibleSize.width + 20) && this->getPositionX() > 40)
    {
        this->setPositionX(this->getPositionX() + speed);    
    }
    else
    {
        speed = -speed;
        this->setPositionX(this->getPositionX() + speed);    
    }

}