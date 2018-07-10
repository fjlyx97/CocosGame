#include "GameClient.h"
#include <cstring>
#include <thread>

GameClient::GameClient()
{
    resetClient();
    this->mSocket = new ODSocket();
    this->mSocket->Init();
    this->mSocket->Create(AF_INET, SOCK_STREAM , 0);

    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(GameClient::sendMsg),
        "sendMsg",
        NULL);
    
	//测试绑定端口
	this->port = 8000;
	strcmp(this->ip, "127.0.0.1");
    bool result = this->mSocket->Connect(this->ip,this->port);

    int retryTimes = 0;
    if (result == true)
    {
		log("连接成功");
        char id[2];
        this->mSocket->Recv(id,2,0);
        this->clientId = atoi(id);
        //通知客户端ID
        NotificationCenter::getInstance()->postNotification("sendClientId",(Ref*)id);
    }
    while (result == false && retryTimes < 7)
    {
        log("retry connecting...");
        result = mSocket->Connect(ip, port);
        retryTimes++;
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            Sleep(500);
        #else
            usleep(500);
        #endif
    }
    std::thread recvMsg = std::thread(&GameClient::recvMsg,this);
    recvMsg.detach();

}

GameClient::~GameClient()
{
    delete this->mSocket;
}

bool GameClient::init()
{
    return true;
}

void GameClient::resetClient()
{
    this->port = 8000;
    strcpy(ip,"127.0.0.1");
}

void GameClient::connectServer()
{
    log("%s",this->ip);
    log("%d",this->port);
}

void GameClient::setClient(char* ip , int port)
{
    strcpy(this->ip,ip);
    this->port = port;
}

void GameClient::recvMsg()
{
    while(true)
    {
        char recvData[50];
        memset(recvData,0,sizeof(recvData));
        this->mSocket->Recv(recvData,3,0);
        int max_size = atoi(recvData);
        memset(recvData,0,sizeof(recvData));
        int result = this->mSocket->Recv(recvData,max_size,0);
        if (result == 0)
        {
            log("断开");
            break;
        }
        //开始处理数据
        //log("%s",recvData);
        char* Info = recvData;
        char cmd[101];
        char strPosX[101];
        char strPosY[101];
        char strRotation[101];
        double posX;
        double posY;
        double rotation;
        int roleIndex = Info[0] - '0';
        int bulletIndex = Info[1] - '0';
        int i;
        int index = 0;
        for (i = 2 ; i < strlen(Info) ; i++)
        {
            if (Info[i] != ',')
            {
                cmd[index++] = Info[i];
            }
            else
            {
                cmd[index] = '\0';
                i++;
                break;
            }
        }
        index = 0;
        for ( ; i < strlen(Info) ; i++)
        {
            if (Info[i] != ',')
            {
                strPosX[index++] = Info[i];
            }
            else
            {
                strPosX[index]  = '\0';
                i++;
                break;
            }
        }
        index = 0;
        for ( ; i < strlen(Info) ; i++)
        {
            if (Info[i] != ',')
            {
                strPosY[index++] = Info[i];
            }
            else
            {
                strPosY[index]  = '\0';
                i++;
                break;
            }
        }
        index = 0;
        for ( ; i < strlen(Info) ; i++)
        {
            if (Info[i] != ',')
            {
                strRotation[index++] = Info[i];
            }
            else
            {
                strRotation[index]  = '\0';
                i++;
                break;
            }
        }
        index = 0;
        for ( ; i < strlen(Info) ; i++)
        {
            strPosY[index++] = Info[i];
        }
        Info[index] = '\0';
        //已经有的数据
        posX = atof(strPosX);
        posY = atof(strPosY);
        rotation = atof(strRotation);

        //log("角色索引 %d 子弹索引 %d 命令 %s X坐标 %lf Y坐标 %lf 转向 %lf",roleIndex,bulletIndex,cmd,posX,posY,rotation);
        if (strcmp(cmd,"addPlayer") == 0)
        {
            index = 0;
            for (auto player : playerTankmanager->returnPlayerTankManager())
            {
                if (index == roleIndex)
                {
					player->setPosition(Vec2(posX,posY));
					player->setRotation(rotation);
                    break;
                }
                index++;
            }
        }
        else if (strcmp(cmd,"addPlayerBullet") == 0)
        {
            roleIndex++;
            bulletIndex++;
            int bulletIndexTemp = 0;
            int bulletIndexAns = 5*(roleIndex-1)+bulletIndex;
            for(auto player : playerTankmanager->returnPlayerTankManager())
            {
                for (auto bullet : *(this->playerBulletmanager->returnPlayerBullet()))
                {
                    //log("%d",bulletIndexTemp);
                    if (bulletIndexTemp == bulletIndexAns)
                    {
                        //log("%d",bulletIndexTemp);
                        bullet->setPosition(Vec2(posX,posY));
                        bullet->setRotation(rotation);
                        break;
                    }
                    bulletIndexTemp++;
                }
            }
        }
        else if (strcmp(cmd,"addEnemy") == 0)
        {
            index = 0;
            for(auto enemy : enemyTankmanager->returnEnemyTankManager())
            {
                if(index == roleIndex)
                {
                    enemy->setPosition(Vec2(posX,posY));
                    enemy->setRotation(rotation);
                    break;
                }
                index++;
            }
        }
        else if(strcmp(cmd,"addEnemyBullet") == 0)
        {
            roleIndex++;
            bulletIndex++;
            int bulletIndexTemp = 0;
            int bulletIndexAns = 5*(roleIndex-1)+bulletIndex;
            for (auto bullet : *(this->enemyBulletmanager->returnPlayerBullet()))
            {
                //log("%d",bulletIndexTemp);
                if (bulletIndexTemp == bulletIndexAns)
                {
                    //log("%d",bulletIndexTemp);
                    bullet->setPosition(Vec2(posX,posY));
                    bullet->setRotation(rotation);
                    break;
                }
                bulletIndexTemp++;
            }
            index = 0;
        }
        else if (strcmp(cmd,"delEnemyBullet") == 0)
        {
            roleIndex++;
            int bulletIndexAns = 5*(roleIndex-1);
            int bulletIndexTemp = 0;
            for (auto bullet : *(this->enemyBulletmanager->returnPlayerBullet()))
            {
                if (bulletIndexTemp >= bulletIndexAns && bulletIndexTemp <= bulletIndexAns+5)
                {
                    bullet->setPosition(Vec2(-1,-1));
                    bullet->setRotation(rotation);
                }
                bulletIndexTemp++;
            }
        }
        else if (strcmp(cmd,"delPlayerBullet") == 0)
        {
            roleIndex++;
            int bulletIndexAns = 5*(roleIndex-1);
            int bulletIndexTemp = 0;
            for (auto bullet : *(this->playerBulletmanager->returnPlayerBullet()))
            {
                if (bulletIndexTemp >= bulletIndexAns && bulletIndexTemp <= bulletIndexAns+5)
                {
                    bullet->setPosition(Vec2(-1,-1));
                    bullet->setRotation(rotation);
                }
                bulletIndexTemp++;
            }
        }
        //log("%s",recvData);
        //将接受到的字符串发送出去处理
        //NotificationCenter::getInstance()->postNotification("sendContent",(Ref*)recvData);
    }
}

void GameClient::bindPlayerTankManager(PlayerTankManager* playerTankmanager)
{
    this->playerTankmanager = playerTankmanager;
}
void GameClient::bindEnemyTankManager(EnemyTankManager* enemyTankmanager)
{
    this->enemyTankmanager = enemyTankmanager;
}
void GameClient::bindEnemyBulletManager(BulletManager* enemyBulletmanager)
{
    this->enemyBulletmanager = enemyBulletmanager;
}
void GameClient::bindPlayerBulletManager(BulletManager* playerBulletmanager)
{
    this->playerBulletmanager = playerBulletmanager;
}
void GameClient::sendMsg(Ref* clientMsg)
{
    //log("%s",clientMsg);
    int sendLen = strlen((char*)clientMsg);
    char sendLenStr[3];
    sendLenStr[1] = sendLen % 10 + '0';
    sendLenStr[0] = sendLen / 10 + '0';
    sendLenStr[2] = '\0';
    this->mSocket->Send((char*)sendLenStr,3,0);
    this->mSocket->Send((char*)clientMsg,strlen((char*)clientMsg),0);
}