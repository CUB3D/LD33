// LD33.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Unknown.h>
#undef main

#include "Loader.h"
#include "Input.h"

#include "CustomEntitys.h"
#include "Map.h"

EntityPlayer* player = NULL;
Map* map = NULL;

void render()
{
	map->render();
}

void update()
{
	map->update();
}

void onClickListener(Unknown::MouseEvent evnt)
{
	if (evnt.mouseButton == Unknown::MouseButton::BUTTON_LEFT)
	{
		if (evnt.buttonState == Unknown::InputState::PRESSED)
		{
			double angle = player->sprite->getAngle();

			EntityBullet* bullet = new EntityBullet(angle, player->sprite->location.x, player->sprite->location.y);

			UK_REGISTER_ENTITY(bullet);

			map->bullets.push_back(bullet);
		}
	}
}

void init()
{
	player = new EntityPlayer(UK_LOAD_SPRITE("Entitys/Player.json"), 100);

	UK_REGISTER_ENTITY(player);

	map = generateRandomMap(1);

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

