#ifndef _BulletManager_H_
#define _BulletManager_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class BulletManager : public Node
{
public:
    BulletManager();
    ~BulletManager();
    void addNewBullet(double bulletRotation,double posX , double posY);
    friend class CollisionDetection;

private:
    int maxBulletNum;
    int BulletNum;
    Vector<Bullet*> playerBullet;

};
#endif