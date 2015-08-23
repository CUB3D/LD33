#ifndef CUSTOM_ENTITYS_H
#define CUSTOM_ENTITYS_H

#include "Entity.h"
#include "Utils.h"
#include "Input.h"
#include "Map.h"

class EntityPlayer : public Unknown::HealthEntity
{
public:
	static int score;

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
	bool isShotByPlayer = false;

	EntityBullet(const double angle, const int x, const int y, bool isShotByPlayer);

	virtual void update() override;

	void move(double sX, double sY);
		
};

class Map;

class EntityGuard : public Unknown::HealthEntity
{
public:
	Map* map;
	EntityPlayer* player;

	EntityGuard(EntityPlayer* player, Map* map);

	virtual void update() override;

	virtual const std::string getEntityID() const override;
};

#endif
