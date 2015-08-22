#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Entity.h"
#include "Image.h"

class Map
{
public:
	std::vector<Unknown::Entity*> entitys;
	Unknown::Graphics::Image* background;

	Map(Unknown::Graphics::Image* background);

	void render();
	void update();
};

static int previousEntityCount;

Map* generateRandomMap(int difficulty);

#endif

