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
    void connectServer(Ref* pdata);
    CREATE_FUNC(GameClient);
    void resetClient();

private:
    ODSocket* mSocket;
    char ip[101];
    int port;

};
#endif