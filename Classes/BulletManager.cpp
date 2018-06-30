#include "BulletManager.h"

BulletManager::BulletManager()
{
    //NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(BulletManager::recvBulletMessage),"PlayerBullet",NULL);
    this->maxBulletNum = 4;
    this->BulletNum = 0;
}

BulletManager::~BulletManager()
{

}

void BulletManager::addNewBullet(double bulletRotation , double posX , double posY,char* path)
{
    //初始化新子弹
    //log("%d",maxBulletNum);
    if (BulletNum <= maxBulletNum)
    {
        auto newBullet = Bullet::create();
        newBullet->bindSprite(Sprite::create(path));
        newBullet->setBulletPos(posX,posY);
        newBullet->setRotation(bulletRotation);
        newBullet->setBulletSpeed(bulletRotation,2);
        newBullet->setPosition(posX,posY);
        newBullet->setScale(0.5);
        //log ("%.2f %.2f" , newBullet->getSprite()->getBoundingBox().size.width, newBullet->getSprite()->getBoundingBox().size.height);
        this->BulletNum++;
        playerBullet.pushBack(newBullet);
        this->addChild(newBullet);
    }

}

void BulletManager::recvBulletMessage(Ref* data)
{
    this->BulletNum--;
}

Vector<Bullet*> BulletManager::returnPlayerBullet()
{
    return this->playerBullet;
}