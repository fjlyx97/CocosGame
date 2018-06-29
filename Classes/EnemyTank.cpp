#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
    this->enemyRotation = 0;
    this->enemyIsAlive = false;
}
EnemyTank::~EnemyTank()
{
}

bool EnemyTank::init()
{
    this->schedule(schedule_selector(EnemyTank::TankMove),1,999,0);
    return true;
}
/*
void EnemyTank::show()
{
    if(getSprite() != NULL)
    {
        setVisible(true);       //设置可见
        enemyIsAlive = true;    //标记坦克为活动状态
    }
}
*/
void EnemyTank::reset()
{
    if(getSprite() != NULL)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->setPosition(Vec2(CCRANDOM_0_1() * visibleSize.width,CCRANDOM_0_1() * visibleSize.height));
    }
    return;
}

bool EnemyTank::isAlive()
{
    return this->enemyIsAlive;
}

int EnemyTank::crashWall()
{
    int state = CCRANDOM_0_1()*5 ;
    return state;
}

void EnemyTank::TankMove(float ft)
{   
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if(this->getPositionX() > visibleSize.width || this->getPositionX() < 0|| this->getPositionY() > (visibleSize.height - 20) || this->getPositionY() < 30)
    {
        return;
    }
    else
    {   
        MoveBy* movebyX;
        MoveBy* movebyY;
        switch(EnemyTank::crashWall())
        {
            case 1:
                speed = 20;
                this->setRotation(90);
                this->enemyRotation = 90;
                movebyX = MoveBy::create(1.0f,Vec2(speed,0));
                this->runAction(movebyX);
                break;
            case 2:
                speed = -20;
                this->setRotation(270);
                this->enemyRotation = 270;
                movebyX = MoveBy::create(1.0f,Vec2(speed,0));
                this->runAction(movebyX);
                break;
            case 3:
                speed = 20;
                this->setRotation(0);
                this->enemyRotation = 0;
                movebyY = MoveBy::create(1.0f,Vec2(0,speed));
                this->runAction(movebyY);
                break;
            case 4:
                speed = -20;
                this->setRotation(180);
                this->enemyRotation = 180;
                movebyY = MoveBy::create(1.0f,Vec2(0,speed));
                this->runAction(movebyY);
                break;
            //default: log("error");break;
        }
    }
    return;
}