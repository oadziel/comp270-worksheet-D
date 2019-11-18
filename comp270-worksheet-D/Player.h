#pragma once
#include "Matrix2D.h"

class Player
{
public:

	// Gets the world-space position of the point where
	// bullets "appear"
	Point2D getGunPosition()
	{
		Matrix2D worldTransform;
		worldTransform.setTransform(m_position, m_rotation);
		return worldTransform * m_localVerts[0];
	}

	// Set the world-space position of the player
	void setPosition(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	// Alter the player's rotation by the given amount
	void rotate(float degrees)
	{
		m_rotation += degrees;
	}

	// Increase the player's speed by the given amount
	// in the direction the player is pointing
	void applyThrust(float t)
	{
		m_speed += t;
		if (m_speed > 2.0f)
			m_speed = 2.0f;
	}

	void update();
	void draw(SDL_Renderer* renderer) const;

	// Gets the player's current speed
	float		getSpeed() const { return m_speed; }

	Vector2D getDirection() const;

private:
	// Vertices of the player's shape in local space
	const Point2D m_localVerts[3] = { Point2D(0, -15), Point2D(-15, 15), Point2D(15, 15) };
	
	Point2D	m_position = Point2D(0.0f, 0.0f);	// World-space position
	float	m_rotation = 0.0f;					// Angle indicating the direction the player is facing
	float	m_speed = 0.0f;						// Speed of travel in the facing direction
	const float m_dragFactor = 0.99f;			// Slows the player down over time
};