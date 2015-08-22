#ifndef CUSTOM_ENTITYS_H
#define CUSTOM_ENTITYS_H

#include "Entity.h"

class EntityPlayer : public Unknown::HealthEntity
{
public:
	EntityPlayer(Unknown::Sprite* sprite, int health);

	virtual void update() override;
};

#endif

