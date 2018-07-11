#include "Vectors.h"

//========
//POINT2D
//========
Point2D::Point2D() : x(0), y(0)
{
}

Point2D::Point2D(const double _x, const double _y) : x(_x), y(_y)
{
}

void Point2D::set(const double newX, const double newY)
{
	x = newX;
	y = newY;
}


//=========
//VECTOR2D
//=========
Vector2D::Vector2D() : x(0), y(0)
{
}

Vector2D::Vector2D(const double _x, const double _y) : x(_x), y(_y)
{
}

void Vector2D::set(const double newX, const double newY)
{
	x = newX;
	y = newY;
}

//normalize the vector to a length of 1 by dividing each side by the current length
void Vector2D::normalize()
{
	const double length = sqrt((x*x) + (y*y));

	if (length > 0)
	{
		x /= length;
		y /= length;
	}
}