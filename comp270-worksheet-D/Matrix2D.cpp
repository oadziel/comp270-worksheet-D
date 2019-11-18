#include "stdafx.h"
#include "Matrix2D.h"

// Sets this matrix to represent a rotation and a translation,
// so as to move a point in world space (rotation is performed first).
void Matrix2D::setTransform(Point2D translation, float rotation)
{
	Matrix2D transMat;
	transMat.m_[0][2] = translation.x;
	transMat.m_[1][2] = translation.y;

	Matrix2D rotMat;
	rotMat.m_[0][0] = rotMat.m_[1][1] = cos(rotation);
	rotMat.m_[1][0] = sin(rotation);
	rotMat.m_[0][1] = -rotMat.m_[1][0];

	*this = transMat * rotMat;
}

// Multiplies the components of a point/vector
void Matrix2D::multiply(float & x, float & y, float & w) const
{
	float x_ = m_[0][0] * x + m_[0][1] * y + m_[0][2] * w,
		y_ = m_[1][0] * x + m_[1][1] * y + m_[1][2] * w,
		w_ = m_[2][0] * x + m_[2][1] * y + m_[2][2] * w;
	x = x_;
	y = y_;
	w = w_;
}
