#include "Player.h"

Player::Player()
{
    this->playerSpeedX = 0;
    this->playerSpeedY = 0;
    this->playerRotation = 0;
    this->playerIsMove = false;
    playerBulletManager = new BulletManager();
    //this->addChild(playerBulletManager);
    this->scheduleUpdate();
}
Player::~Player()
{
    delete playerBulletManager;
}

bool Player::init()
{
    return true;
}

void Player::setPlayerScale(float scale)
{
    getSprite()->setScale(scale);
}

void Player::setPlayerSpeed(float speedX , float speedY)
{
    this->playerSpeedX = speedX;
    this->playerSpeedY = speedY;
}

void Player::setPlayerPos(Vec2 pos)
{
    this->playerX = pos.x;
    this->playerY = pos.y;
}

Vec2 Player::returnPlayerPos()
{
    return Vec2(this->playerX,this->playerY);
}

void Player::actionPlayer(EventKeyboard::KeyCode key , bool isMove)
{
    if (key == EventKeyboard::KeyCode::KEY_J && isMove)
    {
        this->playerBulletManager->addNewBullet(this->playerRotation,this->playerX,this->playerY);
    }
    else
    {
        this->movePlayer(key,isMove);
    }
}

void Player::movePlayer(EventKeyboard::KeyCode key , bool isMove)
{
    this->playerIsMove = isMove;
    if (key == EventKeyboard::KeyCode::KEY_W && isMove)
    {
        this->setPlayerSpeed(0,2);
        this->setRotation(0);
        this->playerRotation = 0;
    }
    else if (key == EventKeyboard::KeyCode::KEY_S && isMove) 
    {
        this->setPlayerSpeed(0,-2);
        this->setRotation(180);
        this->playerRotation = 180;
    }
    else if (key == EventKeyboard::KeyCode::KEY_A && isMove) 
    {
        this->setPlayerSpeed(-2,0);
        this->setRotation(270);
        this->playerRotation = 270;
    }
    else if (key == EventKeyboard::KeyCode::KEY_D && isMove) 
    {
        this->setPlayerSpeed(2,0);
        this->setRotation(90);
        this->playerRotation = 90;
    }
}
void Player::update(float dt)
{
    //log("updating");
    if (this->playerIsMove)
    {
    //    auto visibleSize = Director::getInstance()->getVisibleSize();
        this->playerX += this->playerSpeedX;
        this->playerY += this->playerSpeedY;
        this->setPosition(this->playerX,this->playerY);
  /*      if(this->getPositionX() >= visibleSize.width)
        {
            this->setPosition(Vec2(0,this->getPositionY()));
        }
        if(this->getPositionX() <= 0)
        {
            this->setPosition(Vec2(visibleSize.width + 30,this->getPositionY()));
        }
        if(this->getPositionY() >= visibleSize.height)
        {
            this->setPosition(Vec2(this->getPositionX(),0));
        }
        if(this->getPositionY() <= 0)
        {
            this->setPosition(Vec2(this->getPositionX(),visibleSize.height));
        }  */
    }
}

BulletManager* Player::returnBulletManager()
{
    return this->playerBulletManager;
}