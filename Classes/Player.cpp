#include "Player.h"

Player::Player()
{
    this->playerSpeedX = 0;
    this->playerSpeedY = 0;
    this->playerIsMove = false;
    this->scheduleUpdate();
}
Player::~Player()
{

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

void Player::movePlayer(EventKeyboard::KeyCode key , bool isMove)
{
    this->playerIsMove = isMove;
    if (key == EventKeyboard::KeyCode::KEY_W && isMove)
    {
        this->setPlayerSpeed(0,2);
        this->setRotation(0);
    }
    else if (key == EventKeyboard::KeyCode::KEY_S && isMove) 
    {
        this->setPlayerSpeed(0,-2);
        this->setRotation(180);
    }
    else if (key == EventKeyboard::KeyCode::KEY_A && isMove) 
    {
        this->setPlayerSpeed(-2,0);
        this->setRotation(270);
    }
    else if (key == EventKeyboard::KeyCode::KEY_D && isMove) 
    {
        this->setPlayerSpeed(2,0);
        this->setRotation(90);
    }
}
void Player::update(float dt)
{
    //log("updating");
    if (this->playerIsMove)
    {
        this->playerX += this->playerSpeedX;
        this->playerY += this->playerSpeedY;
        this->setPosition(this->playerX,this->playerY);
    }
}