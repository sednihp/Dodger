#include "Enemy.h"

Enemy::Enemy(unsigned int x, unsigned int maxSpeed, int dim) : dimension(dim),
														alive(true),
														speed(maxSpeed),
														color({ 255,0,255 })	
{
	mBox.h = dimension;
	mBox.w = dimension;

	position.set(static_cast<short>(x), -dimension);
	direction.set(0, 1);
}

Enemy::~Enemy()
{

}

const SDL_Rect Enemy::getBox()
{
	mBox.x = static_cast<Sint16>(position.x);
	mBox.y = static_cast<Sint16>(position.y);

	return mBox;
}

const SDL_Color Enemy::getColor()
{
	return color;
}

//Move the player
//Check if they have collected any powerups and apply them
//If any part of the player moves off the screen, move them back
void Enemy::move(short scrHeight, double deltaTime)
{
	position.y += direction.y * speed * deltaTime;

	if (position.y > scrHeight)
	{
		kill();
	}
}

void Enemy::kill()
{
	alive = false;
}

const bool Enemy::isAlive()
{
	return alive;
}

const int Enemy::getDimension()
{
	return dimension;
}