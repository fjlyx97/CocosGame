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

private:
    Vector<Player*> myPlayer;

};
#endif