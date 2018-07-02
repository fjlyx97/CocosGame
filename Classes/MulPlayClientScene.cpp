#include "MulPlayClientScene.h"
#include <thread>
#include <ODSocket/ODSocket.h>

USING_NS_CC;

Scene* MulPlayClientScene::createScene()
{
    return MulPlayClientScene::create();
}

MulPlayClientScene::MulPlayClientScene()
{
    //初始化连接服务端
    //this->addChild(this->connectClient);
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayClientScene::getConnectIp),
        "sendIp",
        NULL);
    //生成接受玩家消息发送观察者
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayClientScene::updataGameInfo),
        "sendContent",
        NULL);

}

MulPlayClientScene::~MulPlayClientScene()
{
}

bool MulPlayClientScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background_image = Sprite::create("Q版坦克素材/Tiled/bg4.jpg");
    if (background_image == nullptr)
    {
        return false;
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(background_image);
    }


    //创建人物管理器
    playerTankmanager = PlayerTankManager::create();
    //创建怪物管理器
    enemyTankmanager = EnemyTankManager::create();

    this->addChild(playerTankmanager,10);
    this->addChild(enemyTankmanager,10);
    //初始化客户端坦克
    for (int i = 1 ; i <= 6 ; i++)
    {
        playerTankmanager->addNewPlayer();
    }
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        player->setPlayerHidePos();
    }

    return true;
}
void MulPlayClientScene::getConnectIp(Ref* pIpData)
{
    log("%s",pIpData);
    char* ipInfo = (char*)pIpData;
    int i;
    for (i = 0 ; i < strlen(ipInfo) ; i++)
    {
        if (ipInfo[i] != ' ')
        {
            this->ip[i]  = ipInfo[i];
        }
        else
        {
            this->ip[i] = '\0';
            break;
        }
    }
    this->port = 8000;
    std::thread client = std::thread(&MulPlayClientScene::createClient,this);
    client.detach();
}
void MulPlayClientScene::createClient()
{
    log("成功运行");
    gameClientSocket = new GameClient();
    gameClientSocket->retain();
    gameClientSocket->setClient(this->ip,this->port);
    gameClientSocket->connectServer();
}

void MulPlayClientScene::updataGameInfo(Ref* updateInfo)
{
    log("%s",updateInfo);
    char* Info = (char*)updateInfo;
    char cmd[101];
    char strPosX[101];
    char strPosY[101];
    char strRotation[101];
    double posX;
    double posY;
    double rotation;
    int roleIndex = Info[0] - '0';
    int i;
    int index = 0;
    for (i = 1 ; i < strlen(Info) ; i++)
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

    //log("角色索引 %d 命令 %s X坐标 %lf Y坐标 %lf 转向 %lf",roleIndex,cmd,posX,posY,rotation);
    if (strcmp(cmd,"addPlayer") == 0)
    {
        index = 0;
        for (auto player : playerTankmanager->returnPlayerTankManager())
        {
            if (index == roleIndex)
            {
                if (posX != player->getPositionX() || posY != player->getPositionY())
                {
                    player->setPosition(Vec2(posX,posY));
                    player->setRotation(rotation);
                }
                break;
            }
            index++;
        }
    }
    /*
    else if (strcmp(cmd,"addPlayerBullet") == 0)
    {
        index = 0;
        for(auto player : playerTankmanager->returnPlayerTankManager())
        {
            auto bulletManager = player->returnBulletManager();
            if (index == roleIndex)
            {
                bulletManager->addNewBullet(rotation,posX,posY,"Q版坦克素材/bullet/bullet7.png");
                break;
            }
            index++;
        }
    }
<<<<<<< HEAD
    */
    if (strcmp(cmd,"addEnemy") == 0)
=======
    
    else if (strcmp(cmd,"addEnemy") == 0)
>>>>>>> 8271318870f1dac4d5df8572be0ba214991ed962
    {
        index = 0;
        for(auto enemy : enemyTankmanager->returnEnemyTankManager())
        {
            if(index == roleIndex)
            {
<<<<<<< HEAD
                enemy->setPosition(Vec2(posX,posY));
                enemy->setRotation(rotation);
                break;
=======
                enemy->setPosition(posX,posY);
                enemy->setRotation(rotation);
>>>>>>> 8271318870f1dac4d5df8572be0ba214991ed962
            }
            index++;
        }
    }
    
    else if(strcmp(cmd,"addEnemyBullet") == 0 )
    {
        index = 0;
        for(auto enemy2 : enemyTankmanager->returnEnemyTankManager())
        {
            for(auto enemybullet : enemy2->returnBulletManager())
            {
                if(index = roleIndex)
                {
                    enemybullet->addNewBullet(rotation,posX,posY,"Q版坦克素材/bullet/bullet5.png");
                }
            }
        }
        index++;
    }
    */
}

