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
    //初始化观察者
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
        log("监听端口成功");
        log("当前监听端口为：%d",this->port);
        ODSocket* clientSocket = new ODSocket;
        if (mSocket->Accept(*clientSocket,ip))
        {
            connectSocket.push_back(clientSocket);
            NotificationCenter::getInstance()->postNotification("addNewPlayer",NULL);
            std::thread recvThread(GameServer::recvGameMsg,clientSocket,this->currentId);
            recvThread.detach();
            this->currentId++;
        }
        //此处似乎有内存泄露
    }
}

void GameServer::recvGameMsg(ODSocket * clientSocket , int clientId)
{
    char message[1024];
    while (true)
    {
        memset(message,0,sizeof(message));
        int status = clientSocket->Recv(message,1024,0);
        if (status == 0)
        {
            log("客户端已经断开");
            char disconnectMsg[2];
            disconnectMsg[0] = clientId+'0';
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
        delete socket;
    }
}
void GameServer::resetServer()
{
    this->currentId = 0;
    this->port = 8000;
    strcpy(ip,"localhost");
}

void GameServer::disconnectClient(Ref* pdata)
{
    int socketId = atoi((char*)pdata);
    int index = 0;
    std::vector<ODSocket*>::iterator iter;
    for (iter = connectSocket.begin() ; iter != connectSocket.end() ; iter++)
    {
        if (index == socketId)
        {
            connectSocket.erase(iter);
            this->currentId--;
            break;
        }
        index++;
    }
}