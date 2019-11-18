#pragma once

// A class for performing basic operations with homogeneous vectors in 2D space.
// Feel free to edit/extend!
class Vector2D
{
public:
	Vector2D(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_), w(0.0f) {}

	float x, y, w;

	// Get the length of the vector
	float magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	// Make the vector unit length
	void normalise()
	{
		float mag = magnitude();
		x /= mag;
		y /= mag;
	}

	// Vector dot product
	float dot(const Vector2D& other) const
	{
		return x * other.x + y * other.y;
	}

	// Multiply the vector by as scalar
	Vector2D operator*(float scalar) const
	{
		return Vector2D(x * scalar, y * scalar);
	}

	// Multiply the vector by as scalar in place
	void operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
	}
};