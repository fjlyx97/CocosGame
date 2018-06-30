#include "PlayerTankManager.h"

bool PlayerTankManager::init()
{
    return true;
}

PlayerTankManager::PlayerTankManager()
{

}

PlayerTankManager::~PlayerTankManager()
{

}

void PlayerTankManager::addNewPlayer()
{
    auto player = Player::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    player->bindSprite(Sprite::create("Q版坦克素材/plane1.png"));
    player->setPosition(Vec2(CCRANDOM_0_1() * visibleSize.width,CCRANDOM_0_1() * visibleSize.height));
    player->setPlayerScale(0.15);
    player->setPlayerPos(player->getPosition());
    this->addChild(player);
    this->addChild(player->returnBulletManager());//添加子弹管理器
    this->myPlayer.pushBack(player);
}

void PlayerTankManager::recvKey(EventKeyboard::KeyCode keyCode , bool isMove , int playerIndex)
{
    int index = 0;
    for (auto player : myPlayer)
    {
        if (index == playerIndex)
        {
            player->actionPlayer(keyCode,isMove);
            break;
        }
        index++;
    }
}

Vector<Player*> PlayerTankManager::returnPlayerTankManager()
{
    return this->myPlayer;
}