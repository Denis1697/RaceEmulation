#include "Includes.h"

Coordinate::Coordinate(const int& x, const int& y)
{
	x_ = x;
	y_ = y;
}

int 
Coordinate::getX() const
{
	return x_;
}

int 
Coordinate::getY() const
{
	return y_;
}

void 
Coordinate::setX(const int& x)
{
	x_ = x;
}

void 
Coordinate::setY(const int& y)
{
	y_ = y;
}
