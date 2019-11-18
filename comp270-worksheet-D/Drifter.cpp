#include "stdafx.h"
#include "Drifter.h"
#include "Matrix2D.h"

// Update's the Drifter's position, if it is still alive
void Drifter::update()
{
	if (m_alive)
	{
		// Update the position, and anything the derived class wants to
		m_position = m_position + m_velocity;
		updateExtra();
	}
}

// A Bullet is just a dot
void Bullet::draw(SDL_Renderer * renderer) const
{
	if (m_alive)
		SDL_RenderDrawPointF(renderer, m_position.x, m_position.y);
}

// Creates an Asteroid with the given parameters, scaling the points up to the correct size.
Asteroid::Asteroid(Point2D position, Vector2D velocity, float scale, float rotationSpeed) :
	Drifter(position, velocity), m_scale(scale), m_rotationSpeed(rotationSpeed)
{
	for (unsigned i = 0; i < NumVerts; ++i)
		m_localVerts[i] = m_localVerts[i].asVector() * m_scale;
}

// Draws the asteroid on the screen
void Asteroid::draw(SDL_Renderer * renderer) const
{
	if (m_alive)
	{
		// Find the local points in world space by applying a matrix transformation
		Matrix2D worldTransform;
		worldTransform.setTransform(m_position, m_rotation);
		Point2D worldVerts[NumVerts];
		for (unsigned i = 0; i < NumVerts; ++i)
			worldVerts[i] = worldTransform * m_localVerts[i];

		// Draw the transformed points
		for (unsigned i = 0; i < NumVerts - 1; ++i)
			SDL_RenderDrawLineF(renderer, worldVerts[i].x, worldVerts[i].y, worldVerts[i + 1].x, worldVerts[i + 1].y);
		SDL_RenderDrawLineF(renderer, worldVerts[NumVerts - 1].x, worldVerts[NumVerts - 1].y, worldVerts[0].x, worldVerts[0].y);
	}
}

// Returns true if the given point is currently inside the Asteroid, false if not.
bool Asteroid::pointIsInside(Point2D point) const
{
	// Find the local points in world space by applying a matrix transformation
	Matrix2D worldTransform;
	worldTransform.setTransform(m_position, m_rotation);
	Point2D worldVerts[NumVerts];
	for (unsigned i = 0; i < NumVerts; ++i)
		worldVerts[i] = worldTransform * m_localVerts[i];

	// Sum the signed angles between all pairs of vertices and the test point;
	// if the sum is near zero, the point is inside, otherwise it's outside.
	Vector2D v0 = worldVerts[NumVerts-1] - point, v1;
	float len = v0.magnitude();
	if (len < 0.0f)
		return true;	// point and vertex coincide
	v0.normalise();

	float angle = 0.0f, dot;
	for (unsigned i = 0; i < NumVerts; ++i)
	{
		v1 = worldVerts[i] - point;
		len = v1.magnitude();
		if (len < 0.0f)
			return true;	// point and vertex coincide
		v1.normalise();

		// Check if v1 is to the 'left' or 'right' of v0
		dot = v0.dot(v1);
		if (dot < -1.0f)
			angle += M_PI;	// Point lies on the edge, so add 180 degrees
		else if (dot < 1.0f)
		{
			if (v0.x * v1.y - v1.x * v0.y >= 0.0f)
				angle += acosf(dot);
			else
				angle -= acosf(dot);
		}

		// Move to next point
		v0 = v1;
	}

	return fmod( fabs(angle) + M_PI, 4.0f * M_PI ) > 2.0f * M_PI;
}
