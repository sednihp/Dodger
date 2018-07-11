#include "Player.h"

Player::Player(short scrWidth, short scrHeight) : dimension(40), 
													alive(true),
													speed(300),
													color({255,255,0})
{
	position.set((scrWidth - dimension) / 2, scrHeight - 3 * dimension);

	mBox.w = dimension;
	mBox.h = dimension;
}

Player::~Player()
{

}

const SDL_Rect Player::getBox()
{
	mBox.x = static_cast<Sint16>(position.x);
	mBox.y = static_cast<Sint16>(position.y);

	return mBox;
}

const SDL_Color Player::getColor()
{
	return color;
}

void Player::move(short scrWidth, short scrHeight, double deltaTime)
{
	position.x += direction.x * speed * deltaTime;

	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x + dimension > scrWidth)
	{
		position.x = scrWidth - dimension;
	}

	position.y += direction.y * speed * deltaTime;

	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y + dimension > scrHeight)
	{
		position.y = scrHeight - dimension;
	}
}

void Player::kill()
{
	alive = false;
}

const bool Player::isAlive()
{
	return alive;
}

void Player::setDirection(Vector2D newDir)
{
	direction = newDir;
}

void Player::setDirectionX(int newX)
{
	direction.x = newX;
}

void Player::setDirectionY(int newY)
{
	direction.y = newY;
}