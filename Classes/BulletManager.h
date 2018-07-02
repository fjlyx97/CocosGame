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
    void addNewBullet(double bulletRotation, double posX , double posY,char* path , bool server);
    void recvBulletMessage(Ref* data);
    friend class CollisionDetection;
    Vector<Bullet*> returnPlayerBullet();
    virtual bool init();

    CREATE_FUNC(BulletManager);
    
private:
    int maxBulletNum;
    int BulletNum;
    Vector<Bullet*> playerBullet;

};
#endif