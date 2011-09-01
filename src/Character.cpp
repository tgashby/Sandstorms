#include "Character.h"

namespace Sandstorms
{
	Character::Character(std::string texName, int lvl, int xPos /*= 0*/, int yPos /*= 0*/)
	 : level(lvl), position(xPos, yPos), velocity(0.0, 0.0), accel(0.0, 0.0) 
	{
		// Initialize the texture to loadImage(texName.c_str())
		bool loaded = texture.loadTexture(texName.c_str());

		// Initialize the animation with the texture
		animation.setTexture(&texture);

		// Set each corner of the bounds
		bounds.x = xPos;
		bounds.y = yPos;
		bounds.w = texture.getWidth();
		bounds.h = texture.getHeight();

		alive = true;
	}

	Character::~Character() {}

	void Character::takeDamage(int damage)
	{
		// Remove damage from health
		health -= damage;

		// If the health is <= 0
		if(health <= 0)
		{
			alive = false;

			// Delete the animation
			animation.deleteMe();

			// Delete the texture
			texture.deleteMe();
		}
	}

	int Character::getHealth()
	{
		// RETURN current health
		return health;
	}

	TGA::Vector2D Character::getPosition()
	{
		// RETURN the position
		return position;
	}

	SDL_Rect Character::getBounds()
	{
		// RETURN the bounds
		return bounds;
	}

	void Character::increaseAccels(float xAcceleration, float yAcceleration)
	{
		accel += TGA::Vector2D(xAcceleration, yAcceleration);
	}

	void Character::updatePosition()
	{
		position += velocity;

		velocity += accel;

		accel.getX() > 0 ? 
		 accel -= TGA::Vector2D(1, 0) : 
	     accel += TGA::Vector2D(1, 0);
		
		accel -= TGA::Vector2D(0, 1);

		if(position.getY() > 1024)
		{
			position = TGA::Vector2D(position.getX(), 1024);
		}

		if(position.getX() < 0)
		{
			position = TGA::Vector2D(0, position.getY());
		}
	}

	bool Character::isAlive()
	{
		return alive;
	}

	void Character::draw()
	{
		animation.draw(position.getX(), position.getY());
	}

	void Character::setX(float xVal)
	{
		position = position + TGA::Vector2D(xVal, 0);
	}

	void Character::setY(float yVal)
	{
		position = position + TGA::Vector2D(0, yVal);
	}

	void Character::setPosition(float xVal, float yVal)
	{
		position = TGA::Vector2D(xVal, yVal);
	}
}
