// LD33.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <SDL.h>

#include <Unknown.h>
#undef main

#include "Loader.h"
#include "Input.h"

#include "CustomEntitys.h"
#include "Map.h"
#include "Font.h"
#include "UI2D.h"

#include <sstream>
#include <time.h>


EntityPlayer* player = NULL;
Map* map = NULL;

int score = 0;

bool hasDiedYet = false;

Unknown::Graphics::Image failScreen("res/Failscreen.png");

int difficulty = 1;

void restartListener(Unknown::MouseEvent evnt)
{
	Unknown::getUnknown()->quit(0);
}

void render()
{
	if (!player->isAlive())
	{
		if (!hasDiedYet)
		{
			hasDiedYet = true;

			// kill all entitys

			for (auto entity : map->entitys)
			{
				entity->kill();
			}

			UK_MOUSE_LISTENER(restartListener);
		}
		failScreen.render(0, 0);
		return;
	}

	map->render(player);

	const Unknown::Dimension<int>* screenSize = Unknown::getUnknown()->screenSize;

	UK_DRAW_RECT(0, screenSize->height - 20, screenSize->width, 20, Unknown::Colour(200, 200, 200));

	std::stringstream ss;

	ss << "Health: ";

	ss << player->getHealth();

	drawText(ss.str(), 2, screenSize->height - 18);

	std::stringstream ssb;

	ssb << "Score: ";

	ssb << EntityPlayer::score;

	drawText(ssb.str(), 4 + 16 * 13, screenSize->height - 18);

}

bool hasWon()
{
	for (auto ent : map->entitys)
	{
		if (ent->isAlive())
		{
			return false;
		}
	}

	return true;
}

void update()
{
	if (hasWon() && player->isAlive())
	{
		difficulty++;
		//reset

		player = new EntityPlayer(UK_LOAD_SPRITE("Entitys/Player.json"), 100);

		UK_REGISTER_ENTITY(player);

		// generate map

		map = generateRandomMap(difficulty, player);
	}

	if (!player->isAlive())
	{
		return;
	}

	map->update();

	for (auto bullet : map->bullets)
	{
		if (!bullet->isShotByPlayer)
		{
			int a = bullet->sprite->location.x - player->sprite->location.x;
			int b = bullet->sprite->location.y - player->sprite->location.y;
			double dist = sqrt((a * a) + (b * b));

			if (dist < 15)
			{
				player->damage(1);

				bullet->kill();
			}
		}
	}
}

void onClickListener(Unknown::MouseEvent evnt)
{
	if (evnt.mouseButton == Unknown::MouseButton::BUTTON_LEFT)
	{
		if (evnt.buttonState == Unknown::InputState::PRESSED)
		{
			if (player->isAlive())
			{
				double angle = player->sprite->getAngle();

				EntityBullet* bullet = new EntityBullet(angle, player->sprite->location.x + 8, player->sprite->location.y + 8, true);

				UK_REGISTER_ENTITY(bullet);

				map->bullets.push_back(bullet);

				map->hasShotBeenFired = true;
			}
		}
	}
}

void init()
{
	player = new EntityPlayer(UK_LOAD_SPRITE("Entitys/Player.json"), 100);

	UK_REGISTER_ENTITY(player);

	// setup random

	time_t currentTime = 0;

	time(&currentTime);

	srand(currentTime);

	// generate map

	map = generateRandomMap(difficulty, player);

	UK_MOUSE_LISTENER(onClickListener);
}

int main()
{
	UK_UPDATE(update);
	UK_RENDER(render);

	UK_CREATE_WINDOW();

	init();

	UK_INIT_GAME();

	return 0;
}

