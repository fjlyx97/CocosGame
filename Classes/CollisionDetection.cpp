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
    for (auto player : playerTankManager->myPlayer)
    {
        for (auto bullet : player->returnBulletManager()->playerBullet)
        {
            //log("%.2f %.2f",bullet->getBulletPos().x,bullet->getBulletPos().y);
        }
    }
}