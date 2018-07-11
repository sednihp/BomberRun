#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include <vector>

class Point2D
{
public:
	double x, y;

	Point2D();
	Point2D(const double _x, const double _y);

	void set(const double newX, const double newY);
};

class Vector2D
{
public:
	double x, y;

	Vector2D();
	Vector2D(const double _x, const double _y);

	void set(const double newX, const double newY);
	void normalize();
};

#endif // ENUM_H_INCLUDED
