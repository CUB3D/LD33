#ifndef CUSTOM_ENTITYS_H
#define CUSTOM_ENTITYS_H

#include "Entity.h"
#include "Utils.h"
#include "Input.h"

class EntityPlayer : public Unknown::HealthEntity
{
public:
	EntityPlayer(Unknown::Sprite* sprite, int health);

	virtual void update() override;
};

class EntityEnemy : public Unknown::HealthEntity
{
public:
	Unknown::Point<int> direction;
	EntityEnemy(Unknown::Sprite* sprite, int health);

	virtual void update() override;
};

class EntityBullet : public Unknown::TwoStateEntity
{
public:
	Unknown::Point<double> location;

	EntityBullet(const double angle, const int x, const int y);

	virtual void update() override;

	void move(double sX, double sY);
		
};

#endif
