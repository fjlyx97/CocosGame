#include "Bullet.h"

bool Bullet::init()
{
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

}

void Bullet::setBulletSpeed(double bulletRotation)
{
    if (bulletRotation == 0)
    {
        this->bulletSpeedX = 0;
        this->bulletSpeedY = 1;
    }
    else if (bulletRotation == 90)
    {
        this->bulletSpeedX = 1;
        this->bulletSpeedY = 0;
    }
    else if (bulletRotation == 180)
    {
        this->bulletSpeedX = 0;
        this->bulletSpeedY = -1;
    }
    else if (bulletRotation == 270)
    {
        this->bulletSpeedX = -1;
        this->bulletSpeedY = 0;
    }
}

void Bullet::setBulletPos(double posX , double posY)
{
    this->bulletPosX = posX;
    this->bulletPosY = posY;
}

void Bullet::update(float dt)
{
    this->bulletPosX += bulletSpeedX;
    this->bulletPosY += bulletSpeedY;
    this->setPosition(this->bulletPosX,this->bulletPosY);
}

