#include "Bullet.h"

bool Bullet::init()
{
    //订阅消息类型为test的数据，不传递数据
    this->schedule(schedule_selector(Bullet::sendMessage),0);
    return true;
}

Bullet::Bullet()
{
    this->bulletSpeedX = 0;
    this->bulletSpeedY = 0;
    this->scheduleUpdate();
}

Bullet::~Bullet()
{
    //log("delete over");
}
//观察者模式
void Bullet::sendMessage(float dt)
{
    //发布test消息，不传递数据
    NotificationCenter::getInstance()->postNotification("playerBullet",NULL);
}
//观察者模式
void Bullet::testMessage(Ref* sender)
{
    log("testMessage");
}

void Bullet::setBulletSpeed(double bulletRotation , double bulletSpeed)
{
    if (bulletRotation == 0)
    {
        this->bulletSpeedX = 0;
        this->bulletSpeedY = bulletSpeed;
    }
    else if (bulletRotation == 90)
    {
        this->bulletSpeedX = bulletSpeed;
        this->bulletSpeedY = 0;
    }
    else if (bulletRotation == 180)
    {
        this->bulletSpeedX = 0;
        this->bulletSpeedY = -bulletSpeed;
    }
    else if (bulletRotation == 270)
    {
        this->bulletSpeedX = -bulletSpeed;
        this->bulletSpeedY = 0;
    }
    this->bulletRotation = bulletRotation;
}

void Bullet::setBulletPos(double posX , double posY)
{
    this->bulletPosX = posX;
    this->bulletPosY = posY;
}

void Bullet::update(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->bulletPosX += bulletSpeedX;
    this->bulletPosY += bulletSpeedY;
    if (this->bulletPosX > visibleSize.width)
    {
        this->bulletPosX = -1;
    }
    else if (this->bulletPosX < 0)
    {
        this->bulletPosX = visibleSize.width;
    }
    else if (this->bulletPosY > visibleSize.height - 30)
    {
        this->bulletPosY = 10;
    }
    else if (this->bulletPosY < 10)
    {
        this->bulletPosY = visibleSize.height - 30;
    }
    //if((this->bulletPosX > visibleSize.width || this->bulletPosX < 0|| this->bulletPosY > (visibleSize.height - 30) || this->bulletPosY < 10))
    //{   
    //    //观察模式
    //    NotificationCenter::getInstance()->postNotification("PlayerBulletCrashWall",NULL);
    //    this->removeFromParent();
    //}
    this->setPosition(this->bulletPosX,this->bulletPosY);
}

Vec2 Bullet::getBulletPos()
{
    return Vec2(this->bulletPosX,this->bulletPosY);
}
double Bullet::returnBulletRotation()
{
    return this->bulletRotation;
}