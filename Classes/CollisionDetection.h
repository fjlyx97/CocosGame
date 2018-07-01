#ifndef _CollisionDetection_H_
#define _CollisionDetection_H_

#include "cocos2d.h"
#include "EnemyTankManager.h"
#include "PlayerTankManager.h"
#include "EnemyTank.h"

USING_NS_CC;

class CollisionDetection : public Node
{
public:
    CREATE_FUNC(CollisionDetection);
    virtual bool init();
    void bindEnemyTankManager(EnemyTankManager* enemyTankManagerBind);
    void bindPlayerTankManager(PlayerTankManager* playerTankManagerBind);
    
    void update(float dt);
    void tankAI(float dt);
    CollisionDetection();
    ~CollisionDetection();

private:
    EnemyTankManager* enemyTankManager;
    PlayerTankManager* playerTankManager;


};
#endif