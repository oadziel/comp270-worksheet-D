#pragma once
#include "Vector2D.h"

// A class for performing basic operations with homogeneous points in 2D space.
// Feel free to edit/extend!
class Point2D
{
public:
	Point2D(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_), w(1.0f) {}
	Point2D(Vector2D v) : x(v.x), y(v.y), w(1.0f) {}
	
	// Components of the point (distance along each axis)
	float x, y, w;

	// Returns the point as a vector displacement from the origin
	Vector2D asVector() const
	{
		return Vector2D(x, y);
	}

	// Returns the point at the given vector displacement from this point
	Point2D operator+(const Vector2D& vec) const
	{
		return Point2D(x + vec.x, y + vec.y);
	}

	// Returns the vector difference between two points
	Vector2D operator-(const Point2D& other) const
	{
		return Vector2D(x - other.x, y - other.y);
	}
};