#ifndef _Bullet_H_
#define _Bullet_H_

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

class Bullet : public Entity
{
public:
    Bullet();
    ~Bullet();

    void setBulletPos(double posX , double posY);
    void setBulletSpeed(double bulletRotation , double bulletSpeed);
    Vec2 getBulletPos();
    void update(float dt);

    CREATE_FUNC(Bullet);
    virtual bool init();

    double returnBulletRotation();   

    void sendMessage(float dt);

    void testMessage(Ref* sender);

private:
    double bulletPosX;
    double bulletPosY;
    double bulletSpeedX;
    double bulletSpeedY;
    int bulletRotation;
};
#endif