#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include "Util.h"
#include <string>

class Sprite
{
protected:
	Point2D position;
	Vector2D direction;
	std::string image;

public:
	Sprite();
	virtual ~Sprite();

	virtual const Point2D getPosition() const { return position; }
	virtual const Vector2D getDirection() const { return direction; }
	virtual const std::string getImage() const { return image; }
};

#endif // SPRITE_H_INCLUDED