#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
    this->enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
    this->enemyPositionX = 0;
    this->enemyPositionY = 0;
    this->enemyspeedX = 20;
    this->enemyspeedY = 20;
    this->enemyRotation = 0;
    this->enemyIsAlive = false;
    enemyBulletManager = new BulletManager();
}
EnemyTank::~EnemyTank()
{
    delete enemyBulletManager;
}
bool EnemyTank::init()
{
    this->schedule(schedule_selector(EnemyTank::TankAI),0.1f);
    return true;
}
void EnemyTank::reset()
{
    if(getSprite() != NULL)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->setPosition(Vec2(CCRANDOM_0_1()*visibleSize.width,CCRANDOM_0_1()*visibleSize.height));
    }
    return;
}
bool EnemyTank::isAlive()
{
    this->enemyIsAlive = true;
    return this->enemyIsAlive;
}
void EnemyTank::setEnemyScale(float scale)
{
    getSprite()->setScale(scale);
}

void EnemyTank::setEnemySpeed(float speedX, float speedY)
{
    this->enemyspeedX = speedX;
    this->enemyspeedY = speedY;
}
void EnemyTank::setEnemyPos(Vec2 pos)
{
    this->enemyPositionX = pos.x;
    this->enemyPositionY = pos.y;
}
Vec2 EnemyTank::returnEnemyPos()
{
    return Vec2(this->enemyPositionX,this->enemyPositionY);
}
void EnemyTank::TankAI(float ft)
{
    if(this->enemyIsAlive)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();

        if(this->getPositionX() > visibleSize.width + 10 || this->getPositionX() < 10 || this->getPositionY() > (visibleSize.height - 10 ) || this->getPositionY() < 10)
        {
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
        }
        else
        {
            MoveBy* movebyX;
            MoveBy* movebyY;
            auto AI = (int)CCRANDOM_0_1()*5;
            switch(AI)
            {
                case 1:
                    this->setRotation(90);
                    this->enemyRotation = 90;
                    movebyX = MoveBy::create(1.0f,Vec2(enemyspeedX,0));
                    this->runAction(movebyX);
                    break;
                case 2:
                    this->setRotation(270);
                    this->enemyRotation = 270;
                    movebyX = MoveBy::create(1.0f,Vec2(-enemyspeedX,0));
                    this->runAction(movebyX);
                    break;
                case 3:
                    this->setRotation(0);
                    this->enemyRotation = 0;
                    movebyY = MoveBy::create(1.0f,Vec2(0,enemyspeedY));
                    this->runAction(movebyY);
                    break;
                case 4:
                    this->setRotation(180);
                    this->enemyRotation = 180;
                    movebyY = MoveBy::create(1.0f,Vec2(0,-enemyspeedY));
                    this->runAction(movebyY);
                    break;
                //default: log("error");break;
            }
        }
    }
}
BulletManager* EnemyTank::returnBulletManager()
{
    return this->enemyBulletManager;
}

double EnemyTank::returnEnemyTankRotation()
{
    return this->enemyRotation;
}

void EnemyTank::setEnemyRotation(double rotation)
{
    this->enemyRotation = rotation;
}