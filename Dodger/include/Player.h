#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "Sprite.h"

class Player : public Sprite
{
	private:
		const int dimension;
		const int speed;
		SDL_Rect mBox;
		SDL_Color color;
		bool alive;

	public:
		Player(short scrWidth, short scrHeight);
		~Player();

		const SDL_Rect getBox();
		void move(short scrWidth, short scrHeight, double deltaTime);
		const SDL_Color getColor();
		void kill();
		const bool isAlive();
		void setDirection(Vector2D newDir);
		void setDirectionX(int newX);
		void setDirectionY(int newY);
};

#endif
