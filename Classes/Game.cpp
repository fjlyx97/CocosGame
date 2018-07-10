#include "Game.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;

Scene* Game::createScene()
{
	return Game::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	score = 0;

	auto bg = Sprite::create("background.png");
	bg->setScale(5.0);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	//设置分数
	auto Label = Label::createWithSystemFont("Score:", "Arial", 35);
	Label->setPosition(Vec2(70, 700));
	score_label = Label::createWithSystemFont("0", "Arial", 35);
	score_label->setPosition(Vec2(200, 700));
	this->addChild(Label);
	this->addChild(score_label);

	//玩家飞机
	plane = Sprite::create("heroplane.png");
	plane->setTag(1);
	plane->setScale(5.0);
	plane->setPosition(Vec2(240, 100));
	this->addChild(plane,3);

	//时间表方法
	this->scheduleUpdate();
	this->schedule(schedule_selector(Game::new_bullet), 0.5);
	this->schedule(schedule_selector(Game::new_small_enemy), 1);


	//触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	



	return true;
}

bool Game::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void Game::onTouchMoved(Touch *touch, Event *unused_event)
{
	auto sprite = this->getChildByTag(1);
	//log("%f %f", touch->getLocation().x, sprite->getPosition().x);
	if (touch->getLocation().x <= (sprite->getPosition().x + sprite->getBoundingBox().size.width/2) && 
		touch->getLocation().x >= (sprite->getPosition().x - sprite->getBoundingBox().size.width/2) &&
		touch->getLocation().y <= (sprite->getPosition().y + sprite->getBoundingBox().size.height/2) &&
		touch->getLocation().y >= (sprite->getPosition().y - sprite->getBoundingBox().size.height/2) )
	{
		sprite->setPosition(touch->getLocation());
	}
}
void Game::onTouchEnded(Touch *touch, Event *unused_event)
{
	return;
}
void Game::new_bullet(float dt)	//生成子弹
{
	auto hero = this->getChildByTag(1);
	auto bullet = Sprite::create("bullet1.png");
	bullet->setScale(5);
	bullet->setPosition(Vec2(hero->getPosition().x,hero->getPosition().y+50));
	auto moveby = MoveBy::create(3, Vec2(0, 800));
	bullet->runAction(moveby);
	this->addChild(bullet,1);
	bullets.pushBack(bullet);
}
void Game::new_small_enemy(float dt)
{
	auto rand = RandomHelper().random_int(0, 480);
	auto enemy = Sprite::create("enemy1_fly_1.png");
	enemy->setScale(5);
	enemy->setPosition(Vec2(rand, 800));
	auto speed = RandomHelper().random_int(4, 7);
	auto moveby = MoveBy::create(speed, Vec2(0, -900));
	enemy->runAction(moveby);
	small_enemys.pushBack(enemy);
	this->addChild(enemy);
}
void Game::update(float dt)
{
	int flag = 1;
	//判断子弹与敌机
	for (auto bullet = bullets.begin(); bullet != bullets.end(); )
	{
		for (auto enemy = small_enemys.begin(); enemy != small_enemys.end(); )
		{
			if ((*bullet)->boundingBox().intersectsRect((*enemy)->boundingBox()))
			{
				auto bullet_idt = *bullet;
				auto enemy_id = *enemy;
				bullets.eraseObject(*bullet);
				small_enemys.eraseObject(*enemy);
				this->removeChild(bullet_idt,true);
				this->removeChild(enemy_id,true);
				score += 100;
				score_label->setString(Value(score).asString());
				flag = 0;
				break;
			}
			enemy++;
		}
		if (flag == 0)
		{
			break;
		}
		bullet++;
	}
	//子弹超出边界
	for (auto bullet = bullets.begin(); bullet != bullets.end(); )
	{
		if ((*bullet)->getPositionY() >= 800)
		{
			auto bullet_idt = *bullet;
			bullets.eraseObject(bullet_idt);
			this->removeChild(bullet_idt,true);
			break;
		}
		else
		{
			bullet++;
		}
	}
	//敌机超出边界
	for (auto enemy = small_enemys.begin(); enemy != small_enemys.end(); )
	{
		if ((*enemy)->getPositionY() <= 0)
		{
			auto enemy_idt = *enemy;
			small_enemys.eraseObject(enemy_idt);
			this->removeChild(enemy_idt,true);
			break;
		}
		else
		{
			enemy++;
		}
	}
	//判断是否死亡
	for (auto enemy = small_enemys.begin(); enemy != small_enemys.end();)
	{
		if ((*enemy)->boundingBox().intersectsRect(plane->boundingBox()))
		{
			auto over = Label::createWithSystemFont("Game Over", "Arial", 45);
			over->setPosition(Vec2(240, 500));
			this->addChild(over);
		}
		enemy++;
	}
}