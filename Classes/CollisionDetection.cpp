#include "CollisionDetection.h"

bool CollisionDetection::init()
{
    this->scheduleUpdate();
    this->schedule(schedule_selector(CollisionDetection::tankAI),0.5);
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
                if (enemyRec.intersectsRect(bulletRec) || bullet->getPositionX() < 0)
                {
                    //log("子弹%.2f %.2f",bulletRec.size.width,bulletRec.size.height);
                    //log("敌人%.2f %.2f",enemyRec.size.width,enemyRec.size.height);
                    //log("碰撞");
                    //移除子弹
                    bullet->removeFromParent();
                    player->returnBulletManager()->playerBullet.eraseObject(bullet);
                    player->returnBulletManager()->BulletNum -= 1;

                    //被击中的坦克初始化
                    for (auto enemybullet : enemy->returnBulletManager()->returnPlayerBullet())
                    {
                        enemybullet->removeFromParent();
                    }
                    enemy->returnBulletManager()->returnPlayerBullet().clear();
                    enemy->returnBulletManager()->BulletNum = 0 ;
                    enemy->reset();
                    return;
                }
            }
        }
    }
}

void CollisionDetection::tankAI(float dt)
{
    for(auto player1 : playerTankManager->returnPlayerTankManager())
    {
        for(auto enemy : enemyTankManager->enemyTankArr)
        {
            if(enemy->getPositionX() < (player1->returnPlayerPos()).x + 10  && enemy->getPositionX() > (player1->returnPlayerPos()).x - 10)
            {
                //auto enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                if(enemy->getPositionY() < (player1->returnPlayerPos()).y)
                {
                    enemy->setRotation(0);
                    enemy->enemyRotation = 0;
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle);
                }
                else
                {
                    enemy->setRotation(180);
                    enemy->enemyRotation = 180;
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle);
                }
            }
            if(enemy->getPositionY() < (player1->returnPlayerPos()).y + 10  && enemy->getPositionY() > (player1->returnPlayerPos()).y - 10)
            {
                //auto enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                if(enemy->getPositionX() < (player1->returnPlayerPos()).x)
                {
                    enemy->setRotation(90);
                    enemy->enemyRotation = 90;
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle);
                }
                else
                {
                    enemy->setRotation(270);
                    enemy->enemyRotation = 270;
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle);
                }
            }
        }
    }
}