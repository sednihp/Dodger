#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "Sprite.h"

class Enemy : public Sprite
{
	private:
		const int dimension;
		const int speed;
		SDL_Rect mBox;
		SDL_Color color;
		bool alive;

	public:
		Enemy(unsigned int x, unsigned int maxSpeed, int dim);
		~Enemy();

		const SDL_Rect getBox();
		void move(short scrHeight, double deltaTime);
		const SDL_Color getColor();
		void kill();
		const bool isAlive();
		const int getDimension();
};

#endif