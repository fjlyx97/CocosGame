#include "GameServer.h"
#include <thread>
#include <cstring>
#include <cstdlib>

bool GameServer::init()
{
    return true;
}

GameServer::GameServer()
{
    resetServer();
    this->mSocket = new ODSocket();
    this->mSocket->Init();
    this->mSocket->Create(AF_INET, SOCK_STREAM , 0);
    this->mSocket->Bind(this->port);
    //初始化玩家断线观察者
    NotificationCenter::getInstance()->addObserver(
            this,
            callfuncO_selector(GameServer::disconnectClient),
            "playerDisconnect",
            NULL);

    if (!(this->mSocket->Listen(6)))
    {
        log("监听端口失败");
    }
    log("开始监听端口");
    while (true)
    {
        log("当前监听端口为：%d",this->port);
        ODSocket* clientSocket = new ODSocket;
        if (mSocket->Accept(*clientSocket,ip))
        {
            for (int i = 0 ; i < 6 ; i++)
            {
                if (this->bookId[i] == 0)
                {
                    this->bookId[i] = 1;
                    playerClient* newPlayer = new playerClient(clientSocket,i);
                    connectSocket.push_back(newPlayer);
                    log("新玩家连入，id为%d",i);
                    NotificationCenter::getInstance()->postNotification("addNewPlayer",NULL);
                    std::thread recvThread(GameServer::recvGameMsg,newPlayer);
                    recvThread.detach();
                    break;
                }
            }
            this->currentId++;
        }
        //此处似乎有内存泄露
    }
}

void GameServer::recvGameMsg(playerClient * newPlayer)
{
    char message[1024];
    while (true)
    {
        memset(message,0,sizeof(message));
        int status = newPlayer->connectSocket->Recv(message,1024,0);
        if (status == 0)
        {
            //log("客户端已经断开");
            char disconnectMsg[2];
            disconnectMsg[0] = newPlayer->id+'0';
            disconnectMsg[1] = '\0';
            NotificationCenter::getInstance()->postNotification("playerDisconnect",(Ref*)disconnectMsg);
            break;
        }
        NotificationCenter::getInstance()->postNotification("playerAction",(Ref*)message);
    }
}

GameServer::~GameServer()
{
    this->mSocket->Clean();
    for (auto socket : connectSocket)
    {
        delete socket->connectSocket;
    }
}
void GameServer::resetServer()
{
    this->currentId = 0;
    this->port = 8000;
    memset(this->bookId,0,sizeof(this->bookId));
    strcpy(ip,"localhost");
}

void GameServer::disconnectClient(Ref* pdata)
{
    int socketId = atoi((char*)pdata);
    int index = 0;
    std::vector<playerClient*>::iterator iter;
    for (iter = connectSocket.begin() ; iter != connectSocket.end() ; iter++)
    {
        if (index == socketId)
        {
            connectSocket.erase(iter);
            //log("当前%d玩家退出",socketId);
            bookId[socketId] = 0;
            break;
        }
        index++;
    }
}