#include "stdafx.h"
#include "CustomEntitys.h"

#include "Input.h"
#include "Vector.h"


EntityPlayer::EntityPlayer(Unknown::Sprite* sprite, int health) : HealthEntity(sprite, health)
{
}

void EntityPlayer::update()
{
	int mouseX = 0;
	int mouseY = 0;

	SDL_GetMouseState(&mouseX, &mouseY);

	Unknown::Vector mouse(mouseX, mouseY);

	Unknown::Vector player(this->sprite->location.x, this->sprite->location.y);

	int angle = player.getAngleTo(mouse);

	angle -= 360;

	if (angle < 0)
		angle = -angle;

	this->sprite->setAngle(angle);

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_LEFT))
	{
		this->sprite->location.x--;
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_RIGHT))
	{
		this->sprite->location.x++;
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_DOWN))
	{
		this->sprite->location.y++;
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_UP))
	{
		this->sprite->location.y--;
	}
}
