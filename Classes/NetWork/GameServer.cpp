#include "GameServer.h"
#include <string>
#include <thread>
#include <cstring>
#include <cstdlib>

bool GameServer::init()
{
    return true;
}

GameServer::GameServer()
{
    //初始化监听IP，端口
    resetServer();
    //初始化玩家断线观察者
    NotificationCenter::getInstance()->addObserver(
            this,
            callfuncO_selector(GameServer::disconnectClient),
            "playerDisconnect",
            NULL);
    
    //初始化发送玩家位置观察者（似乎没用）
    NotificationCenter::getInstance()->addObserver(
            this,
            callfuncO_selector(GameServer::sendNewPlayerPos),
            "sendNewPlayerPos",
            NULL);

    //初始化发送位置观察者
    NotificationCenter::getInstance()->addObserver(
            this,
            callfuncO_selector(GameServer::sendOldPlayer),
            "sendOldPlayerPos",
            NULL);
    
   

    
}

void GameServer::setIp(char* ip , int port)
{
    this->port = port;
    strcpy(this->ip,ip);
}


void GameServer::recvGameMsg(playerClient * newPlayer)
{
    this->mutexMsg.lock();
    char getMsg[20];
    while (true)
    {
        memset(getMsg,0,sizeof(getMsg));
        newPlayer->connectSocket->Recv(getMsg,3,0);
        int dataLen = atoi(getMsg);

        memset(getMsg,0,sizeof(getMsg));
        int status = newPlayer->connectSocket->Recv(getMsg,dataLen,0);
        if (status == 0)
        {
            log("客户端已经断开");
            char disconnectMsg[2];
            disconnectMsg[0] = newPlayer->id+'0';
            disconnectMsg[1] = '\0';
            //NotificationCenter::getInstance()->postNotification("playerDisconnect",(Ref*)disconnectMsg);
            break;
        }
        //log("%d",this->MsgQueue.front());
        //log("%s" , this->MsgQueue.front());

        char cmd[20];
        int getClientId = getMsg[0] - '0';
        int i;
        for (i = 1 ; i < strlen(getMsg) ; i++)
        {
            cmd[i-1] = getMsg[i];
        }
        cmd[i-1] = '\0';
        //log("%d %s",getClientId,cmd);
        if (strcmp(cmd,"playerUp") == 0)
        {
            this->playerTankmanager->recvKey(EventKeyboard::KeyCode::KEY_W,true,getClientId);
        }
        else if (strcmp(cmd,"playerDown") == 0)
        {
            this->playerTankmanager->recvKey(EventKeyboard::KeyCode::KEY_S,true,getClientId);
        }
        else if (strcmp(cmd,"playerLeft") == 0)
        {
            this->playerTankmanager->recvKey(EventKeyboard::KeyCode::KEY_A,true,getClientId);
        }
        else if (strcmp(cmd,"playerRight") == 0)
        {
            this->playerTankmanager->recvKey(EventKeyboard::KeyCode::KEY_D,true,getClientId);
        }
        else if (strcmp(cmd,"playerAttack") == 0)
        {
            this->MsgQueue->push(getClientId);
        }
        else if (strcmp(cmd,"playerStop") == 0)
        {
            this->playerTankmanager->recvKey(EventKeyboard::KeyCode::KEY_K,false,getClientId);
        }
        //NotificationCenter::getInstance()->postNotification("playerAction",(Ref*)message);
    }
    this->mutexMsg.unlock();
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
    strcpy(ip,"127.0.0.1");
}

//关联玩家掉线广播
void GameServer::disconnectClient(Ref* pdata)
{
    int socketId = atoi((char*)pdata);
    int index = 0;
    std::vector<playerClient*>::iterator iter;
    for (iter = connectSocket.begin() ; iter != connectSocket.end() ; iter++)
    {
        if (index == socketId)
        {
            //connectSocket.erase(iter);
            //log("当前%d玩家退出",socketId);
            bookId[socketId] = 0;
            break;
        }
        index++;
    }
}

//发送新玩家坐标广播
void GameServer::sendNewPlayerPos(Ref* pos)
{
    int sendPlayerId = ((char*)(pos))[0]-48;
    connectSocket[sendPlayerId]->connectSocket->Send((char*)pos,strlen((char*)pos));
}

//向新玩家发送所有数据
void GameServer::sendOldPlayer(Ref* pdata)
{
    //此处发送数据，代码待编写
    //log("%s",pdata);
    char* sendMsg = (char*)pdata;
    int i = 0;
    for (auto client : connectSocket)
    {
        if (bookId[i] == 1)
        {
            int size = strlen(sendMsg);
            char max_size[3];
            max_size[1] = size % 10 + 48;
            max_size[0] = size / 10 + 48;
            max_size[2] = '\0';
            client->connectSocket->Send(max_size,3);
            client->connectSocket->Send(sendMsg,strlen(sendMsg));
            //client->connectSocket->Clean();
        }
        i++;
    }
}

void GameServer::bindEnemyTankManager(EnemyTankManager* enemyTankmanager)
{
    this->enemyTankmanager = enemyTankmanager;
}
void GameServer::bindPlayerTankManager(PlayerTankManager* playerTankmanager)
{
    this->playerTankmanager = playerTankmanager;
}
void GameServer::start()
{
    this->mSocket = new ODSocket();
    this->mSocket->Init();
    this->mSocket->Create(AF_INET, SOCK_STREAM , 0);
    this->mSocket->Bind(this->port);
    log("开启的IP:%s,port:%d",this->ip,this->port);
    if (!(this->mSocket->Listen(6)))
    {
        log("监听端口失败");
    }
    //log("开始监听端口");
    this->bookId[0] = 1;
    while (true)
    {
        log("当前监听端口为：%d",this->port);
        ODSocket* clientSocket = new ODSocket;
        if (mSocket->Accept(*clientSocket,this->ip))
        {
            for (int i = 0 ; i < 6 ; i++)
            {
                if (this->bookId[i] == 0)
                {
                    this->bookId[i] = 1;
                    playerClient* newPlayer = new playerClient(clientSocket,i);
                    connectSocket.push_back(newPlayer);
                    log("新玩家连入，id为%d",i);
                    char sendIdMsg[2];
                    sendIdMsg[0] = i+'0';
                    sendIdMsg[1] = '\0';
                    newPlayer->connectSocket->Send(sendIdMsg,2,0);
                    NotificationCenter::getInstance()->postNotification("addNewPlayer",(Ref*)sendIdMsg);
                    std::thread recvThread = std::thread(&GameServer::recvGameMsg,this,newPlayer);
                    recvThread.detach();
                    //测试代码
                    /*
                    for (int j = 0 ; j < 6 ; j++)
                    {
                        log("%d ",this->bookId[j]);
                    }
                    */
                    //测试代码
                    break;
                }
            }
            this->currentId++;
        }
        //此处似乎有内存泄露
    }
}
void GameServer::bindMsgQueue(std::queue<int>* MsgQueue)
{
    this->MsgQueue = MsgQueue;
}