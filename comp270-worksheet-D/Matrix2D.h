#pragma once
#include "Point2D.h"

// A class for performing basic 2D transformation operations with homogeneous matrices.
// Feel free to edit/extend!
class Matrix2D
{
public:
	// Const accessor for individual components.
	const float& operator()(unsigned i, unsigned j) const
	{
		return m_[i][j];
	}

	// Writable accessor for individual components.
	float& operator()(unsigned i, unsigned j)
	{
		return m_[i][j];
	}

	// Apply this matrix to a vector
	Vector2D operator*(const Vector2D& vec) const
	{
		Vector2D result(vec);
		multiply(result.x, result.y, result.w);
		return result;
	}

	// Apply this matrix to a point
	Point2D operator*(const Point2D& pt) const
	{
		Point2D result(pt);
		multiply(result.x, result.y, result.w);
		return result;
	}

	// Apply another matrix to this one
	Matrix2D operator*(const Matrix2D& right)
	{
		Matrix2D result(right);
		multiply(result(0, 0), result(1, 0), result(2, 0));
		multiply(result(0, 1), result(1, 1), result(2, 1));
		multiply(result(0, 2), result(1, 2), result(2, 2));
		return result;
	}

	void setTransform(Point2D translation, float rotation);

private:
	float	m_[3][3] = { { 1.0f, 0.0f, 0.0f },
							{ 0.0f, 1.0f, 0.0f },
							{ 0.0f, 0.0f, 1.0f }};

	void multiply(float& x, float& y, float& w) const;

};