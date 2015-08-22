#include "stdafx.h"
#include "Map.h"

#include "CustomEntitys.h"
#include "Loader.h"

#include <iostream>


Map::Map(Unknown::Graphics::Image* background) : background(background), entitys()
{
}

void Map::render()
{
	background->render(0, 0, 0);

	for (auto entity : this->entitys)
	{
		entity->render();
	}
}

void Map::update()
{
	for (auto entity : this->entitys)
	{
		entity->update();
	}
}

Map* generateRandomMap(int difficulty)
{
	int currentEntityCount = rand() % 50 + 1;

	previousEntityCount += currentEntityCount;

	std::cout << "Generating map with " << previousEntityCount << " entitys" << std::endl;

	Unknown::Graphics::Image* background = new Unknown::Graphics::Image("res/Background_1.png");

	Map* map = new Map(background);

	const Unknown::Dimension<int>* screenSize = Unknown::getUnknown()->screenSize;

	for (int i = 0; i < previousEntityCount; i++)
	{
		Unknown::Sprite* enemySprite = UK_LOAD_SPRITE("Entitys/EnemySprite.json");

		enemySprite->location.x = rand() % screenSize->width + enemySprite->bounds.size.width + 1;
		enemySprite->location.y = rand() % screenSize->height + enemySprite->bounds.size.height + 1;

		EntityEnemy* enemy = new EntityEnemy(enemySprite, 10);
		map->entitys.push_back(enemy);
	}

	return map;
}
