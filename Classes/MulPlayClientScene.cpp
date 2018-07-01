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

    this->addChild(playerTankmanager);
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
    //log("%s",updateInfo);
    char* Info = (char*)updateInfo;
    char cmd[20];
    char strPosX[20];
    char strPosY[20];
    int posX;
    int posY;
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
        strPosY[index++] = Info[i];
    }
    Info[index] = '\0';
    posX = atoi(strPosX);
    posY = atoi(strPosY);
    //log("角色索引 %d 命令 %s X坐标 %d Y坐标 %d",roleIndex,cmd,posX,posY);
    if (strcmp(cmd,"addPlayer") == 0)
    {
        index = 0;
        for (auto player : playerTankmanager->returnPlayerTankManager())
        {
            if (index == roleIndex)
            {
                player->setPosition(Vec2(posX,posY));
                break;
            }
            index++;
        }
    }
}