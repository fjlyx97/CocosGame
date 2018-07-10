#include "CollisionDetection.h"
#include <string>

bool CollisionDetection::init()
{
    this->scheduleUpdate();
    this->schedule(schedule_selector(CollisionDetection::tankAI),1);
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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    //玩家子弹触墙判断
	int flag = 0;
    for(auto player : playerTankManager->returnPlayerTankManager())
    {
        for(auto bullet : player->returnBulletManager()->playerBullet)
        {
            if(bullet->getPositionX() < 0 || bullet->getPositionX() > visibleSize.width || bullet->getPositionY() < 0 || bullet->getPositionY() > visibleSize.height)
            {
                bullet->removeFromParent();
                player->returnBulletManager()->playerBullet.eraseObject(bullet);
                player->returnBulletManager()->BulletNum -= 1;
				flag = 1;
				break;
            }
        }
		if (flag)
			break;
    }

    //敌方子弹触墙判断
	flag = 0;
    for(auto enemy : enemyTankManager->enemyTankArr)
    {
        for(auto bullet : enemy->returnBulletManager()->playerBullet)
        {
            if(bullet->getPositionX() < 0 || bullet->getPositionX() > visibleSize.width || bullet->getPositionY() < 0 || bullet->getPositionY() > visibleSize.height)
            {
                bullet->removeFromParent();
                enemy->returnBulletManager()->playerBullet.eraseObject(bullet);
                enemy->returnBulletManager()->BulletNum -= 1;
				flag = 1;
				break;
            }
        }
		if (flag)
			break;
    }

    int playerIndex = 0;

    //子弹与敌人碰撞判断
    for (auto player : playerTankManager->returnPlayerTankManager())
    {
        for (auto bullet : player->returnBulletManager()->playerBullet)
        {
            //log("%.2f %.2f",bullet->getBulletPos().x,bullet->getBulletPos().y);
            //得到每个子弹以后判断是否和敌人碰撞
            int enemyIndex = 0;
            for (auto enemy : enemyTankManager->enemyTankArr )
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
                    //bullet->setPosition(Vec2(200,200));
                    bullet->removeFromParent();
                    
                    player->returnBulletManager()->playerBullet.eraseObject(bullet);
                    player->returnBulletManager()->BulletNum -= 1;

                    //被击中的坦克重新初始化位置
                    //发送被击中坦克的ID
                    std::string posX,posY,sendPosMsg,rotation;
                    sendPosMsg = Value(enemyIndex).asString()+"9"+"delEnemyBullet"+","+"-1"+","+"-1"+"0"+"\n";
                    NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));

                    sendPosMsg = Value(playerIndex).asString()+"9"+"delPlayerBullet"+","+"-1"+","+"-1"+"0"+"\n";
                    NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
                    for (auto enemybullet : *(enemy->returnBulletManager()->returnPlayerBullet()))
                    {
                        enemybullet->removeFromParent();
                    }
                    enemy->returnBulletManager()->returnPlayerBullet()->clear();
                    enemy->returnBulletManager()->BulletNum = 0 ;
                    enemy->reset();

                    return;
                }
                enemyIndex++;
            }
        }
        playerIndex++;
    }

    //子弹与玩家碰撞判断
	flag = 0;
    for(auto enemy : enemyTankManager->enemyTankArr)
    {
        for(auto bullet : enemy->returnBulletManager()->playerBullet)
        {
            for(auto player : playerTankManager->returnPlayerTankManager())
            {
                auto playerRec = player->getBoundingBox();
                auto bulletRec = bullet->getBoundingBox();
                if(playerRec.intersectsRect(bulletRec))
                {
                    bullet->removeFromParent();
                    enemy->returnBulletManager()->playerBullet.eraseObject(bullet);
                    enemy->returnBulletManager()->BulletNum -= 1;
					flag = 1;
                    log("Game Over");
					break;
                }
            }
			if (flag)
				break;
        }
		if (flag)
			break;
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
                    char* enemyTankBulletStyle = "QTank/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
                else
                {
                    enemy->setRotation(180);
                    enemy->enemyRotation = 180;
                    char* enemyTankBulletStyle = "QTank/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
            }
            if(enemy->getPositionY() < (player1->returnPlayerPos()).y + 10  && enemy->getPositionY() > (player1->returnPlayerPos()).y - 10)
            {
                //auto enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                if(enemy->getPositionX() < (player1->returnPlayerPos()).x)
                {
                    enemy->setRotation(90);
                    enemy->enemyRotation = 90;
                    char* enemyTankBulletStyle = "QTank/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
                else
                {
                    enemy->setRotation(270);
                    enemy->enemyRotation = 270;
                    char* enemyTankBulletStyle = "QTank/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
            }
        }
    }
}