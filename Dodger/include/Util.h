#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "SDL_pixels.h"

namespace Dodger
{
	//compares two SDL_Colors to see if they're equivalent
	inline const bool sameColor(SDL_Color const &lhs, SDL_Color const &rhs)
	{
		if(lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b)
		{
			return true;
		}

		return false;
	}
}

class Point2D
{
public:
	double x, y;

	Point2D();
	Point2D(double _x, double _y);

	void set(double newX, double newY);
};

class Vector2D
{
public:
	double x, y;

	Vector2D();
	Vector2D(double _x, double _y);

	void set(double newX, double newY);
	void normalize();
};

#endif