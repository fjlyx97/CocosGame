#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
    this->enemyIsAlive = false;
}
EnemyTank::~EnemyTank()
{
}

bool EnemyTank::init()
{
    return true;
}

bool EnemyTank::isAlive()
{
    return this->enemyIsAlive;
}