#pragma once
#include "Point2D.h"

// A Drifter is something that travels across the screen with a constant velocity
class Drifter
{
public:
	Drifter(Point2D position, Vector2D velocity) : m_position(position), m_velocity(velocity) {}
	virtual ~Drifter() {}

	// Get the current (world) position
	Point2D		getPosition() const { return m_position; }

	// Get the current velocity vector
	Vector2D	getVelocity() const { return m_velocity; }

	// Returns true if the projectile is still active
	// (has not been killed)
	bool		isAlive() const { return m_alive; }

	void update();
	void kill() { m_alive = false; }

	// Derived types should draw themselves
	virtual void draw(SDL_Renderer * renderer) const = 0;

protected:
	// Allow derived classes to perform extra updates
	// (called in update())
	virtual void updateExtra() {}

	Point2D m_position;		// Current world-space position
	Vector2D m_velocity;	// Current velocity
	bool	m_alive = true;	// True if the projectile is still active
};

// A Bullet is just a basic Drifter that doesn't do anything else
class Bullet : public Drifter
{
public:
	Bullet(Point2D position, Vector2D velocity) : Drifter(position, velocity) {}
	virtual ~Bullet() {}

	virtual void draw(SDL_Renderer * renderer) const;

private:
};

// An Asteroid is a Drifter that also has a (constant) angular speed
class Asteroid : public Drifter
{
public:
	Asteroid(Point2D position, Vector2D velocity, float scale = 1.0f, float rotationSpeed = 0.001f);
	virtual ~Asteroid() {}

	virtual void draw(SDL_Renderer * renderer) const;

	float	getScale() const { return m_scale; }
	bool	pointIsInside(Point2D point) const;

protected:
	// Increase the rotation by a fixed amount each time update() is called.
	virtual void updateExtra() { m_rotation += m_rotationSpeed; }

private:
	// Vertices of the player's shape in local space
	static const unsigned NumVerts = 10;
	Point2D m_localVerts[NumVerts] = { Point2D(0.0f, 1.2f), Point2D(0.6f, 0.9f),
									Point2D(0.6f, 0.3f), Point2D(1.2f, 0.0f),
									Point2D(0.9f, -0.6f), Point2D(0.3f, -0.6f),
									Point2D(0.0f, -0.9f), Point2D(-0.6f, -0.6f),
									Point2D(-1.2f, 0.0f), Point2D(-0.9f, 0.9f) };

	float m_rotation = 0.0f;		// Current rotation angle
	float m_rotationSpeed = 0.001f;	// Amount by which to 
	float m_scale = 1.0f;			// Asteroid's size (scale applied to the vertices)
};