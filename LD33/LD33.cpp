// LD33.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Unknown.h>
#undef main

#include <Loader.h>

#include "CustomEntitys.h"

EntityPlayer* player = NULL;

void render()
{
	player->render();
}

void update()
{
	player->update();
}

void init()
{
	player = new EntityPlayer(UK_LOAD_SPRITE("Entitys/Player.json"), 100);
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

