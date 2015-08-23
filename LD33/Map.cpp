#include "stdafx.h"
#include "Map.h"

#include "CustomEntitys.h"

#include "Loader.h"
#include "Physics.h"
#include "UI2D.h"
#include "Font.h"

#include <iostream>
#include <sstream>


Map::Map(Unknown::Graphics::Image* background) : background(background), entitys()
{
	this->policeTimer = 15 * 60;
}

void Map::render()
{
	background->render(0, 0, 0);

	for (auto entity : this->entitys)
	{
		if (entity->isAlive())
		{
			entity->render();
		}
	}

	if (this->hasShotBeenFired)
	{
		const Unknown::Dimension<int>* screenSize = Unknown::getUnknown()->screenSize;

		int barScale = 5;
		int widthScale = 3;

		UK_DRAW_RECT(screenSize->width / barScale - 2, 2, screenSize->width / barScale * widthScale + 4, 14, Unknown::Colour::BLACK);

		UK_DRAW_RECT(screenSize->width / barScale, 4, screenSize->width / barScale * widthScale, 10, Unknown::Colour::RED);

		double percent = policeTimer / (15.0 * 60.0);

		double percentB = percent * (screenSize->width / barScale * widthScale);

		UK_DRAW_RECT(screenSize->width / barScale, 4, percentB, 10, Unknown::Colour::GREEN);

		std::stringstream ss;

		ss << "The police arrive in: ";

		ss << (policeTimer / 60);

		drawText(ss.str(), screenSize->width / barScale - 64, 18);
	}
}

void Map::update()
{
	if (hasShotBeenFired)
	{
		policeTimer--;
	}

	for (auto entity : this->entitys)
	{
		if (entity->isAlive())
		{
			entity->update();
		}
	}

	// Collision check

	for (auto bullet : bullets)
	{
		for (auto entity : entitys)
		{
			if (bullet->isAlive() && entity->isAlive())
			{
				//if not shot by player ->  don't damage guard

				if (!bullet->isShotByPlayer && entity->getEntityID() == "GUARD")
				{
				}
				else
				{
					int a = bullet->sprite->location.x - entity->sprite->location.x;
					int b = bullet->sprite->location.y - entity->sprite->location.y;
					double dist = sqrt((a * a) + (b * b));

					if (dist < 15)
					{
						entity->damage(1);

						if (!entity->isAlive())
						{
							EntityPlayer::score += 100;
						}


						bullet->kill();
					}
				}

			}
		}
	}
}

Map* generateRandomMap(int difficulty, EntityPlayer* player)
{
	int currentEntityCount = rand() % 25 + 1;

	previousEntityCount += currentEntityCount;

	std::cout << "Generating map with " << previousEntityCount << " entitys" << std::endl;

	Unknown::Graphics::Image* background = new Unknown::Graphics::Image("res/Background_1.png");

	Map* map = new Map(background);

	const Unknown::Dimension<int>* screenSize = Unknown::getUnknown()->screenSize;

	int amountGuard = rand() % previousEntityCount / 2 + 1;

	for (int i = 0; i < previousEntityCount - amountGuard; i++)
	{
		Unknown::Sprite* enemySprite = UK_LOAD_SPRITE("Entitys/EnemySprite.json");

		enemySprite->location.x = rand() % screenSize->width + enemySprite->bounds.size.width + 1;
		enemySprite->location.y = rand() % screenSize->height + enemySprite->bounds.size.height + 1;

		EntityEnemy* enemy = new EntityEnemy(enemySprite, 5);
		map->entitys.push_back(enemy);
	}

	for (int i = 0; i < amountGuard; i++)
	{
		EntityGuard* guard = new EntityGuard(player, map);

		guard->sprite->location.x = rand() % screenSize->width + guard->sprite->bounds.size.width + 1;
		guard->sprite->location.y = rand() % screenSize->height + guard->sprite->bounds.size.height + 1;

			
		map->entitys.push_back(guard);
	}

	return map;
}
