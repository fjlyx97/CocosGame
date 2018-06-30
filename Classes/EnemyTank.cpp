#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
    this->enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
    enemyBulletManager = new BulletManager();
    this->enemyRotation = 0;
    this->enemyIsAlive = false;
}
EnemyTank::~EnemyTank()
{
    delete enemyBulletManager;
}

bool EnemyTank::init()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
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
        this->setPosition(Vec2(CCRANDOM_0_1()*visibleSize.width,visibleSize.height-100));
    }
    return;
}

bool EnemyTank::isAlive()
{
    return this->enemyIsAlive;
}

int EnemyTank::crashWall()
{
    int state = CCRANDOM_0_1()*5;
    return state;
}
void EnemyTank::TankMove(float ft)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if(this->getPositionX() > visibleSize.width + 10 || this->getPositionX() < 10 || this->getPositionY() > (visibleSize.height - 10 ) || this->getPositionY() < 10)
    {
     //   MoveTo* moveto = MoveTo::create(10,Vec2(visibleSize.width/2,visibleSize.height/2));
     //  this->runAction(moveto);
      //  this->setPosition(this->playerX,this->playerY);
        if(this->getPositionX() > visibleSize.width + 10)
        {
            this->setPosition(Vec2(10,this->getPositionY()));
        }
        if(this->getPositionX() < 10)
        {
            this->setPosition(Vec2(visibleSize.width + 10,this->getPositionY()));
        }
        if(this->getPositionY() > visibleSize.height - 10)
        {
            this->setPosition(Vec2(this->getPositionX(),10));
        }
        if(this->getPositionY() < 10)
        {
            this->setPosition(Vec2(this->getPositionX(),visibleSize.height - 10));
        } 
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
    if(CCRANDOM_0_1() < 0.05)
    {
        this->enemyBulletManager->addNewBullet(this->enemyRotation,this->getPositionX(),this->getPositionY(),enemyTankBulletStyle);
    }
    return;
}
BulletManager* EnemyTank::returnBulletManager()
{
    return this->enemyBulletManager;
}
