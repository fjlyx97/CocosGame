#include "CollisionDetection.h"
#include <string>

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
            int enemyIndex = 0;
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

                    //被击中的坦克重新初始化位置
                    //发送被击中坦克的ID
                    std::string posX,posY,sendPosMsg,rotation;
                    sendPosMsg = Value(enemyIndex).asString()+"9"+"delEnemyBullet"+","+"-1"+","+"-1"+"0"+"\n";
                    NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));

                    for (auto enemybullet : enemy->returnBulletManager()->returnPlayerBullet())
                    {
                        enemybullet->setPosition(Vec2(-1,-1));
                        enemybullet->removeFromParent();
                    }
                    enemy->returnBulletManager()->returnPlayerBullet().clear();
                    enemy->returnBulletManager()->BulletNum = 0 ;
                    enemy->reset();


                    enemyIndex++;
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
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
                else
                {
                    enemy->setRotation(180);
                    enemy->enemyRotation = 180;
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
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
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
                else
                {
                    enemy->setRotation(270);
                    enemy->enemyRotation = 270;
                    char* enemyTankBulletStyle = "Q版坦克素材/bullet/bullet5.png";
                    enemy->returnBulletManager()->addNewBullet(enemy->enemyRotation,enemy->getPositionX(),enemy->getPositionY(),enemyTankBulletStyle,true);
                }
            }
        }
    }
}
/*
cocos2d::Animate* CollisionDetection::createAnimate(float posX, float posY)
{

    SpriteFrame* frame = NULL;
    Vector<SpriteFrame*> framevec;
    //用一个列表保存所有SpriteFrame对象
    for(int i = 1; i <= 4; i++)
    {
        frame = frameCache->getSpriteFrameByName(StringUtils::format("%d.png",i),Rect(0,0,130,130));
        frameVec.pushBack(frame);
    }

    //使用SpriteFrame列表创建动画对象
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.2f);

    //把动画包装成一个动作
    Animate* action = Animate::create(animation);

    return action;
}
*/