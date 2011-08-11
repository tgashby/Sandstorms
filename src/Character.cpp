#include "Character.h"

namespace Sandstorms
{
	Character::Character(std::string texName, int lvl, int xPos /*= 0*/, int yPos /*= 0*/)
	 : level(lvl)
	{
		// Initialize the texture to loadImage(texName.c_str())
		// Set coords x
		// Set coords y
	}

	Character::~Character() {}

	void Character::takeDamage(int damage)
	{
		// Remove damage from health

		// If the health is <= 0
			// Delete the animation
			// Delete the texture
	}

	int Character::getHealth()
	{
		// RETURN current health
	}

	SDL_Point Character::getPosition()
	{
		// RETURN the position
	}

	SDL_Rect Character::getBounds()
	{
		// RETURN the bounds
	}

	void Character::setX( int xVal )
	{
		// Set the coords.x
	}

	void Character::setY( int yVal )
	{
		// Set the coords.y
	}

	void Character::setPosition( SDL_Point newCoords )
	{
		// Set the coords
	}
}
