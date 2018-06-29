#ifndef _GameServer_H_
#define _GameServer_H_
#include "cocos2d.h"
#include "ODSocket/ODSocket.h"
#include <string>
USING_NS_CC;
class GameServer : public Ref
{
public:
    GameServer();
    ~GameServer();
    virtual bool init();
    CREATE_FUNC(GameServer);

private:
    ODSocket* mSocket;
    //Vector<ODSocket*> connectSocket;
    std::string ip;
    int port;
};
#endif