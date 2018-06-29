#include "BulletManager.h"

BulletManager::BulletManager()
{
    this->maxBulletNum = 4;
    this->BulletNum = 0;
}

BulletManager::~BulletManager()
{

}

void BulletManager::addNewBullet(double bulletRotation , double posX , double posY)
{
    //初始化新子弹
    //log("%d",maxBulletNum);
    if (BulletNum <= maxBulletNum)
    {
        auto newBullet = Bullet::create();
        newBullet->bindSprite(Sprite::create("Q版坦克素材/bullet/bullet1.png"));
        newBullet->setBulletPos(posX,posY);
        newBullet->setRotation(bulletRotation);
        newBullet->setBulletSpeed(bulletRotation,2);
        newBullet->setPosition(posX,posY);
        //newBullet->setScale(1.2);
        //log ("%.2f %.2f" , newBullet->getSprite()->getBoundingBox().size.width, newBullet->getSprite()->getBoundingBox().size.height);
        this->BulletNum++;
        playerBullet.pushBack(newBullet);
        this->addChild(newBullet);
    }
}
