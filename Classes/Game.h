#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;
class Game : public cocos2d::Scene
{
private:
	Vector <Sprite*> bullets;
	Vector <Sprite*> small_enemys;
	Sprite* plane;
	int score;
	Label* score_label;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//触摸选项
	bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);

	//刷新选项
	void update(float dt);

	//生成子弹和敌机
	void new_bullet(float dt);
	void new_small_enemy(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(Game);
};

#endif // __Game_SCENE_H__

