#ifndef _Entity_H_
#define _Entity_H_
#include "cocos2d.h"
USING_NS_CC;

class Entity : public Node
{
public:
    Entity();
    ~Entity();
    Sprite* getSprite();
    void bindSprite(Sprite* sprite);
private:
    Sprite* m_sprite;
};
#endif