#include "Player.h"

Player::Player()
{
    this->playerBulletStyle = "QTank/bullet/bullet7.png";
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
    //getSprite()->setScale(scale);
	this->setScale(scale);
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
    this->setPlayerSpeed(0,0);
    if (key == EventKeyboard::KeyCode::KEY_J && isMove)
    {
        this->playerBulletManager->addNewBullet(this->playerRotation,this->playerX,this->playerY,this->playerBulletStyle,true);
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
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->playerX += this->playerSpeedX;
        this->playerY += this->playerSpeedY;
        this->setPosition(this->playerX,this->playerY);

        if(this->getPositionX() > visibleSize.width + 20 || this->getPositionX() < 10 || this->getPositionY() > (visibleSize.height) || this->getPositionY() < 10)
        {
            if(this->getPositionX() > visibleSize.width + 20)
            {
                this->playerX = 10;
                this->setPosition(Vec2(10,this->getPositionY()));
            }
            if(this->getPositionX() < 10)
            {
            
                this->playerX = visibleSize.width + 20;
                this->setPosition(Vec2(visibleSize.width + 20,this->getPositionY()));
            }
            if(this->getPositionY() > visibleSize.height)
            {
                this->playerY = 10;
                this->setPosition(Vec2(this->getPositionX(),10));
            }
            if(this->getPositionY() < 10)
            {
                this->playerY = visibleSize.height;
                this->setPosition(Vec2(this->getPositionX(),visibleSize.height));
            }  
        }
    }
}


BulletManager* Player::returnBulletManager()
{
    return this->playerBulletManager;
}

void Player::setPlayerHidePos()
{
    this->setPosition(Vec2(-1,-1));
}

void Player::setPlayerServerPos()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(Vec2(CCRANDOM_0_1() * visibleSize.width,CCRANDOM_0_1() * visibleSize.height));
}

double Player::returnPlayerRotation()
{
    return this->playerRotation;
}