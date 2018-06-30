#ifndef _PlayerTankManager_H_
#define _PlayerTankManager_H_
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class PlayerTankManager : public Node
{
public:
    PlayerTankManager();
    ~PlayerTankManager();
    virtual bool init();
    CREATE_FUNC(PlayerTankManager);


    void addNewPlayer();
    void recvKey(EventKeyboard::KeyCode keyCode , bool isMove , int playerIndex);
    Vector<Player*> returnPlayerTankManager();

    //实现碰撞的友元类
    //friend class CollisionDetection;


private:
    Vector<Player*> myPlayer;

};
#endif