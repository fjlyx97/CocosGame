#ifndef _GameClient_H_
#define _GameClient_H_
#include "cocos2d.h"
#include "ODSocket/ODSocket.h"
USING_NS_CC;

class GameClient : public Ref
{
public:
    GameClient();
    ~GameClient();
    virtual bool init();
    CREATE_FUNC(GameClient);

private:

};
#endif