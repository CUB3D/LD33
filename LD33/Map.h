#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Entity.h"
#include "Image.h"

#include "CustomEntitys.h"

class EntityBullet;
class EntityPlayer;

class Map
{
public:
	std::vector<Unknown::Entity*> entitys;
	std::vector<EntityBullet*> bullets;
	Unknown::Graphics::Image* background;
	bool hasShotBeenFired = false;
	int policeTimer = 0;
	bool hasPoliceArrived = false;

	Map(Unknown::Graphics::Image* background);

	void render(EntityPlayer* player);
	void update();
};

static int previousEntityCount;

class EntityPlayer;

Map* generateRandomMap(int difficulty, EntityPlayer* player);

#endif

