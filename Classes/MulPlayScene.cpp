#include "SimpleAudioEngine.h"
#include "Entity.h"
#include "EnemyTankManager.h"
#include "HelloWorldScene.h"
#include "NetWork/GameServer.h"
#include "MulPlayScene.h"
#include <thread>
#include <cstring>
#include <string>
USING_NS_CC;

MulPlayScene::MulPlayScene()
{
    this->playerNum = 0;
    memset(this->bookPlayer,0,sizeof(this->bookPlayer));
}

MulPlayScene::~MulPlayScene()
{
    if (playerGameServer != NULL)
    {
        delete playerGameServer;
    }
}


bool MulPlayScene::init()
{
    if ( !Scene::init())
    {
        return false;
    }
    //初始化游戏背景
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
    //创建怪物管理器
    enemyTankmanager = EnemyTankManager::create();
    //创建人物管理器
    playerTankmanager = PlayerTankManager::create();
    //初始化碰撞检测管理器
    collisionDetectionTank = CollisionDetection::create();
    collisionDetectionTank->bindEnemyTankManager(enemyTankmanager);
    collisionDetectionTank->bindPlayerTankManager(playerTankmanager);
    this->addChild(enemyTankmanager,10);
    this->addChild(playerTankmanager,10);
    this->addChild(collisionDetectionTank,10);
    //初始化服务器端玩家坦克
    for (int i = 1 ; i <= 6 ; i++)
    {
        playerTankmanager->addNewPlayer();
    }
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        player->setPlayerHidePos();
    }

    std::thread server(MulPlayScene::serverStart,this->playerGameServer);
    server.detach();
    //开启玩家消息监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::recvServer),
        "playerAction",
        NULL);
    //开启玩家连接监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::serverAddNewPlayer),
        "addNewPlayer",
        NULL);
    //开启玩家断线监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::serverDeletePlayer),
        "playerDisconnect",
        NULL);

    return true;
}

void MulPlayScene::sendPosition()
{
    int index = 0;
    std::string posX,posY,sendPosMsg;
    for(auto otherPlayer : playerTankmanager->returnPlayerTankManager())
    {   
        posX = otherPlayer->getPositionX();
        posY = otherPlayer->getPositionY();
        std::string id = Value(index).asString();
        sendPosMsg = id + "addPlayer" + "," + posX + "," + posY + '\n';
        index++;
        //NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
    }
    index = 0;
    for(auto enemy : enemyTankmanager->returnEnemyTankManager())
    {
        posX = enemy->getPositionX();
        posY = enemy->getPositionY();
        std::string id = Value(index).asString();
        sendPosMsg = id + "addEnemy" + "," + posX + "," + posY + '\n';
        index++;
        //NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
    }
    index = 0;
    for(auto playerbullet : playerBulletmanager->returnPlayerBullet())
    {
        posX = playerbullet->getPositionX();
        posY = playerbullet->getPositionY();
        std::string id = Value(index).asString();
        sendPosMsg = id + "addPlayerBullet" + "," + posX + "," + posY + '\n';
        index++;
        //NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
    }
    index = 0;
    for(auto enemybullet : enemyBulletmanager->returnPlayerBullet())
    {
        posX = enemybullet->getPositionX();
        posY = enemybullet->getPositionY();
        std::string id = Value(index).asString();
        sendPosMsg = id + "addEnemyBullet" + "," + posX + "," + posY + '\n';
        index++;
        //NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
    }
    
}

void MulPlayScene::serverStart(GameServer* playerGameServer)
{
    playerGameServer = new GameServer();
    playerGameServer->retain();
}
//关联客户端玩家发送信息的广播
void MulPlayScene::recvServer(Ref* playerAction)
{
    log("%s",playerAction);
}
//关联新增玩家的广播
void MulPlayScene::serverAddNewPlayer(Ref* newPlayer)
{
    int index = 0;
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        if (index == playerNum)
        {
            player->setPlayerServerPos();
            //这里需要向新玩家发送老玩家坐标
            
            //NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
            //这里编写
            //怪物管理器，玩家管理器，玩家管理器中的子弹管理器，怪物管理器中的子弹管理器
            //是不是任务量爆炸
            //所以我也很难受啊，那本书里面460开始，有一章是讲json的，似乎可以帮我们减轻工作量，你可以阅读试试
            //我先补完客户端的连接部分
            //你要把怪物的坐标整合起来，用逗号作为分割，前缀为add，那个id没必要加，因为它是当下唯一确定
            //不仅是怪物的坐标，还有玩家子弹的目标
            //你可以自己约定一个数据 比如addplayer,addplayerbullet,addenemy
            //反正用逗号进行分割，我到时候客户端通过你编写的数据进行添加数
            //这里编写
            //刚刚发现ID也要组合，格式按照我下面那样
            
                    
            //这里需要往已经存在的玩家发送新玩家坐标
            std::string posX = Value(player->getPositionX()).asString();
            std::string posY = Value(player->getPositionY()).asString();
            for (int i = 0 ; i < 6 ; i++)
            {
                std::string id = Value(i).asString();
                if (this->bookPlayer[i] == 1)
                {
                    //格式在这里
                    std::string sendPosMsg = id +"add"+',' + posX+','+posY+'\n';
                    NotificationCenter::getInstance()->postNotification("sendNewPlayerPos",(Ref*)((char*)sendPosMsg.data()));
                }
            }
            break;
        }
        index++;
    }
    this->bookPlayer[atoi((char*)newPlayer)] = 1;
    this->playerNum++;
}

//关联删除玩家的广播（未完成）
void MulPlayScene::serverDeletePlayer(Ref* delPlayer)
{
    int playerId = atoi((char*)delPlayer);
    this->bookPlayer[playerId] = 0;
    int index = 0;
    for (auto player : this->playerTankmanager->returnPlayerTankManager())
    {
        if (index == playerId)
        {
            player->removeFromParent();
            playerTankmanager->returnPlayerTankManager().eraseObject(player);
            break;
        }
        index++;
    }
}

