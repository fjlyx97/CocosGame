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
    //if (playerGameServer != NULL)
    //{
    //    delete playerGameServer;
    //}
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
    auto background_image = Sprite::create("QTank/Tiled/bg4.jpg");
    if (background_image == nullptr)
    {
        return false;
    }
    else
    {
        background_image->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(background_image);
    }


    //开启按键监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MulPlayScene::onKeyPressed,this);
    listener->onKeyReleased = CC_CALLBACK_2(MulPlayScene::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

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
    int index = 0;

    //初始化房主玩家
    this->playerNum++;
    this->bookPlayer[0] = 1;
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        if (index == 0)
        {
            index++;
            continue;
        }
        player->setPlayerHidePos();
    }

    //服务器打开BOT
    for (auto enemy : this->enemyTankmanager->returnEnemyTankManager())
    {
        enemy->isAlive();
    }
    

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
    //开启获得IP监听
    NotificationCenter::getInstance()->addObserver(
        this,
        callfuncO_selector(MulPlayScene::sendIp),
        "sendIp",
        NULL);
    
    //this->scheduleUpdate();
    this->schedule(schedule_selector(MulPlayScene::update),0.05f);

    std::thread server = std::thread(&MulPlayScene::serverStart,this,this->playerGameServer,this->ip,this->port);
    server.detach();
    return true;
}

void MulPlayScene::sendPosition()
{
    int index = 0;
    std::string posX,posY,sendPosMsg,rotation;
    int playerIndex = 9;
	int flag = 0;
    for(auto otherPlayer : playerTankmanager->returnPlayerTankManager())
    {   
        posX = Value(otherPlayer->getPositionX()).asString();
        posY = Value(otherPlayer->getPositionY()).asString();
		if (temp_x != otherPlayer->getPositionX() || temp_y != otherPlayer->getPositionY() && flag == 1)
		{
			temp_x = otherPlayer->getPositionX();
			temp_y = otherPlayer->getPositionY();
			rotation = Value(Value(otherPlayer->returnPlayerRotation()).asInt()).asString();
			std::string id = Value(index).asString();
			//std::string playerId = Value(playerIndex).asString();
			sendPosMsg = id + '9' + "addPlayer" + "," + posX + "," + posY + "," + rotation +"\n";
			index++;
			NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
		}
		flag++;
    }
    index = 0;
    int enemyIndex = 9;
    for(auto enemy : enemyTankmanager->returnEnemyTankManager())
    {
        posX = Value(enemy->getPositionX()).asString();
        posY = Value(enemy->getPositionY()).asString();
        rotation = Value(Value(enemy->returnEnemyTankRotation()).asInt()).asString();
        std::string id = Value(index).asString();
        std::string enemyId = Value(enemyIndex).asString();
        sendPosMsg = id + enemyId + "addEnemy" + "," + posX + "," + posY + "," + rotation + "\n";
        index++;
        NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
    }
    index = 0;
    playerIndex = 0;
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        index = 0;
        for (auto bullet : *(player->returnBulletManager()->returnPlayerBullet()))
        {
            posX = Value(bullet->getPositionX()).asString();
            posY = Value(bullet->getPositionY()).asString();
            rotation = Value(Value(bullet->returnBulletRotation()).asInt()).asString();
            std::string id = Value(index).asString();
            std::string playerId = Value(playerIndex).asString();
            sendPosMsg = playerId + id + "addPlayerBullet" + "," + posX + "," + posY + "," + rotation + "\n";
            index++;
            NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
        }
        playerIndex++;
    }
    index = 0;
    enemyIndex = 0;
    for (auto enemyTank : this->enemyTankmanager->returnEnemyTankManager())
    {
        index = 0;
        for (auto enemybullet : *(enemyTank->returnBulletManager()->returnPlayerBullet()))
        {
            posX = Value(enemybullet->getPositionX()).asString();
            posY = Value(enemybullet->getPositionY()).asString();
            rotation = Value(Value(enemybullet->returnBulletRotation()).asInt()).asString();
            std::string id = Value(index).asString();
            std::string enemyId = Value(enemyIndex).asString();
            sendPosMsg = enemyId + id + "addEnemyBullet" + "," + posX + "," + posY + "," + rotation + "\n";
            index++;
            NotificationCenter::getInstance()->postNotification("sendOldPlayerPos",(Ref*)((char*)sendPosMsg.data()));
        }
        enemyIndex++;
    }
}

void MulPlayScene::serverStart(GameServer* playerGameServer , char* ip , int port)
{
    playerGameServer = GameServer::create();
    playerGameServer->retain();
    playerGameServer->bindPlayerTankManager(this->playerTankmanager);
    playerGameServer->bindEnemyTankManager(this->enemyTankmanager);
    playerGameServer->bindMsgQueue(&this->MsgQueue);
    playerGameServer->start();
}
//关联客户端玩家发送信息的广播（未完成）
void MulPlayScene::recvServer(Ref* playerAction)
{
    //log("%s",playerAction);
    
}
//关联新增玩家的广播
void MulPlayScene::serverAddNewPlayer(Ref* newPlayer)
{
    int index = 0;
    int currentNum = atoi((char*)newPlayer);
    for (auto player : playerTankmanager->returnPlayerTankManager())
    {
        if (index == currentNum)
        {
            player->setPlayerServerPos();
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
    //log("%d",playerId);
    this->bookPlayer[playerId] = 0;
    int index = 0;
    for (auto player : this->playerTankmanager->returnPlayerTankManager())
    {
        if (index == playerId)
        {
            player->setPlayerHidePos();
            break;
        }
        index++;
    }
}

void MulPlayScene::update(float dt)
{
    this->updateMutex.lock();
    for (int i = 1 ; i < 3 ; i++)
    {
        if (this->bookPlayer[i] == 1)
        {
            this->sendPosition();
        }
    }
    while(!(this->MsgQueue.empty()))
    {
        int choice = this->MsgQueue.front();
		log("%d", choice);
        this->playerTankmanager->recvKey(EventKeyboard::KeyCode::KEY_J,true,choice);
        this->MsgQueue.pop();
    }
    this->updateMutex.unlock();
}

void MulPlayScene::sendIp(Ref* ipData)
{
    char* ipInfo = (char*)ipData;
    //分割字符串
    int i;
    //log("%s",ipInfo);
    for (i = 0 ; i < strlen(ipInfo) ; i++)
    {
        if (ipInfo[i] == ' ')
        {
            break;
        }
        this->ip[i] = ipInfo[i];
    }
    this->port = atoi(&ipInfo[i+1]);
    log("%s %d",this->ip,this->port);

    //std::thread server(MulPlayScene::serverStart,this->playerGameServer,this,this->ip,this->port);
    //std::thread server = std::thread(&MulPlayScene::serverStart,this,this->playerGameServer,this->ip,this->port);
    //server.detach();

    //NotificationCenter::getInstance()->postNotification("sendServerIp",ipData);
}

void MulPlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode ,Event * event)
{
    this->playerTankmanager->recvKey(keyCode,true,0);
}

void MulPlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode ,Event * event)
{
    this->playerTankmanager->recvKey(keyCode,false,0);
}