#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Entity.h"
#include "Image.h"

#include "CustomEntitys.h"

class Map
{
public:
	std::vector<Unknown::Entity*> entitys;
	std::vector<EntityBullet*> bullets;
	Unknown::Graphics::Image* background;

	Map(Unknown::Graphics::Image* background);

	void render();
	void update();
};

static int previousEntityCount;

Map* generateRandomMap(int difficulty);

#endif

