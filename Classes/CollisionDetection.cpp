#include "CollisionDetection.h"

bool CollisionDetection::init()
{
    this->scheduleUpdate();
    return true;
}


CollisionDetection::CollisionDetection()
{

}

CollisionDetection::~CollisionDetection()
{

}

void CollisionDetection::bindEnemyTankManager(EnemyTankManager* enemyTankManagerBind)
{
    this->enemyTankManager = enemyTankManagerBind;
}

void CollisionDetection::bindPlayerTankManager(PlayerTankManager* playerTankManagerBind)
{
    this->playerTankManager = playerTankManagerBind;
}

void CollisionDetection::update(float dt)
{
    for (auto player : playerTankManager->returnPlayerTankManager())
    {
        for (auto bullet : player->returnBulletManager()->playerBullet)
        {
            //log("%.2f %.2f",bullet->getBulletPos().x,bullet->getBulletPos().y);
            //得到每个子弹以后判断是否和敌人碰撞
            for (auto enemy : enemyTankManager->enemyTankArr)
            {
                //log("%.2f %.2f",enemy->getPosition().x,enemy->getPosition().y);
                //得到玩家位置
                auto bulletRec = bullet->boundingBox();
                auto enemyRec = enemy->boundingBox();
                if (enemyRec.intersectsRect(bulletRec))
                {
                    //log("子弹%.2f %.2f",bulletRec.size.width,bulletRec.size.height);
                    //log("敌人%.2f %.2f",enemyRec.size.width,enemyRec.size.height);
                    //log("碰撞");
                    //移除子弹
                    bullet->removeFromParent();
                    player->returnBulletManager()->playerBullet.eraseObject(bullet);
                    player->returnBulletManager()->BulletNum -= 1;

                    //被击中的坦克重新初始化位置
                    enemy->reset();
                    enemy->returnBulletManager()->playerBullet.clear();
                    //enemy->returnBulletManager()->BulletNum -= 1;
                    
                    return;
                }
            }
        }
    }
    
}