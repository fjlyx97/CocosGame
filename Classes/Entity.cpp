#include "PlayerScene.h"
#include "Entity.h"

Entity::Entity()
{
    m_sprite = NULL;
}

Entity::~Entity(){}   

sprite* Entity::getSprite()
{
    return this->m_sprite;
}

void Entity::bindSprite(Sprite* sprite)
{
    this->m_Sprite = sprite;
    this->addChild(m_sprite);
}