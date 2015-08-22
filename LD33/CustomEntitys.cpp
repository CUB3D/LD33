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

EntityEnemy::EntityEnemy(Unknown::Sprite* sprite, int health) : HealthEntity(sprite, health)
{
}

void EntityEnemy::update()
{
	if (!(rand() % 100))
	{
		Unknown::Vector nodeVector(rand() % 200 + 1, rand() % 200 + 1);
		Unknown::Vector locationVector(this->sprite->location.x, this->sprite->location.y);

		int angle = nodeVector.getAngleTo(locationVector);

		this->sprite->setAngle(angle);

		direction.x = rand() % 3 - 1;
		direction.y = rand() % 3 - 1;
	}

	if ((this->sprite->location.x <= 10 || this->sprite->location.x >= 600))
	{
		Unknown::Vector nodeVector(rand() % 200 + 1, rand() % 200 + 1);
		Unknown::Vector locationVector(this->sprite->location.x, this->sprite->location.y);

		int angle = nodeVector.getAngleTo(locationVector);

		this->sprite->setAngle(angle);

		direction.x = !direction.x;
	}

	if ((this->sprite->location.y <= 10 || this->sprite->location.y >= 600))
	{
		Unknown::Vector nodeVector(rand() % 200 + 1, rand() % 200 + 1);
		Unknown::Vector locationVector(this->sprite->location.x, this->sprite->location.y);

		int angle = nodeVector.getAngleTo(locationVector);

		this->sprite->setAngle(angle);

		direction.y = !direction.y;
	}

	this->sprite->location.x += direction.x;
	this->sprite->location.y += direction.y;
}
