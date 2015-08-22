#include "stdafx.h"
#include "CustomEntitys.h"

#include "Input.h"
#include "Vector.h"
#include "Loader.h"


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

EntityBullet::EntityBullet(const double angle, const int x, const int y) : TwoStateEntity(UK_LOAD_SPRITE("Entitys/BulletSprite.json"))
{
	this->sprite->location.x = x;
	this->sprite->location.y = y;
	this->location.x = x;
	this->location.y = y;
	this->sprite->setAngle(angle - 90);
}

#define BULLET_SPEED 10

void EntityBullet::update()
{
	this->move(1, 1);

	Unknown::Unknown* uk = Unknown::getUnknown();

	if (this->sprite->location.x + 70 < 0 || this->sprite->location.x - 70 > uk->screenSize->width)
	{
		this->kill();
	}

	if (this->sprite->location.y < 0 || this->sprite->location.y - 70 > uk->screenSize->height)
	{
		this->kill();
	}
}

void EntityBullet::move(double sX, double sY)
{
	Unknown::Vector velocity(this->sprite->direction.x * sX, this->sprite->direction.y * sY);

	if (velocity.getLength() > 0)
	{
		velocity.normalize();
	}

	this->location.x += velocity.x * BULLET_SPEED;
	this->location.y += velocity.y * BULLET_SPEED;

	this->sprite->location.x = location.x;
	this->sprite->location.y = location.y;

	this->sprite->bounds.location.x = location.x;
	this->sprite->bounds.location.y = location.y;
}
