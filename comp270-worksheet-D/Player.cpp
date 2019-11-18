#include "stdafx.h"
#include "Player.h"

// Updates the player's position and speed from
// the keyboard-controlled values.
void Player::update()
{
	// Get the direction in world space
	Vector2D direction = getDirection();
	
	// Find the velocity vector and use it to update the position
	Vector2D velocity = direction * m_speed;
	m_position = m_position + velocity;

	// Apply drag
	m_speed *= m_dragFactor;
}

// Draws the player on the screen
void Player::draw(SDL_Renderer* renderer) const
{
	// Find the local points in world space by applying a matrix transformation
	Matrix2D worldTransform;
	worldTransform.setTransform(m_position, m_rotation);
	Point2D worldVerts[3];
	for (unsigned i = 0; i < 3; ++i)
		worldVerts[i] = worldTransform * m_localVerts[i];

	// Draw the transformed points
	SDL_RenderDrawLineF(renderer, worldVerts[0].x, worldVerts[0].y, worldVerts[1].x, worldVerts[1].y);
	SDL_RenderDrawLineF(renderer, worldVerts[1].x, worldVerts[1].y, worldVerts[2].x, worldVerts[2].y);
	SDL_RenderDrawLineF(renderer, worldVerts[2].x, worldVerts[2].y, worldVerts[0].x, worldVerts[0].y);
}

// Gets the player's current world-space facing direction
// as a normalised vector
Vector2D Player::getDirection() const
{
	// Get the current world transform
	Matrix2D worldTransform;
	worldTransform.setTransform(m_position, m_rotation);

	// Get the direction in world space
	Vector2D direction = m_localVerts[0].asVector();
	direction = worldTransform * direction;

	direction.normalise();
	return direction;
}
