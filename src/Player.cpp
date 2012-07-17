#include "Player.h"

namespace Sandstorms
{
	Player::Player(std::string texName, int lvl, int xPos, int yPos) 
		: Character(texName, 1337, xPos, yPos)
	{
		// Set hasJumped to false
		hasJumped = false;

		// Set hasDoubleJumped to false
		hasDoubleJumped = false;

		// Add animation frames (multi-line)
		// ....
		// ....
		SDL_Rect currFrame;

		currFrame.x = 0;
		currFrame.y = 0;
		currFrame.w = 15;
		currFrame.h = 30;

		animation.addFrame(currFrame, 500000);

		currFrame.x = 15;

		animation.addFrame(currFrame, 500000);
	}

	Player::~Player(void) {}

	void Player::initAttributes(int level)
	{
		// Set health to 250
		health = 250;

		// Set speed to 5? (I dunno)
		speed = 5;
	}

	void Player::moveToward(Character& who)
	{

	}

	void Player::attack(Character& who)
	{
		// IF the current is a MeleeAttack
			// IF the attack's range is within the who's bounds
				// Damage that Character with the attack's strength
		// ELSE (it's a ranged attack)
			// Send the ranged attack in the direction of mouse
	}

	void Player::updatePosition()
	{
		if(position.getY() > 512 || accel.getY() < -10)
		{
			accel.setY(0);
			hasDoubleJumped = false;
			hasJumped = false;
		}

		Character::updatePosition();
	}

	void Player::changeAttack(int attackNum)
	{
		// Change the current attack to attackNum

	}

	void Player::jump()
	{
		// If the player has not double jumped
		if(!hasDoubleJumped)
		{
			// Add 10 to the player's y velocity
			increaseAccels(0, 10);
		}

		// If the player has jumped
		if(hasJumped)
		{
			// Set the double jump
			hasDoubleJumped = true;
		}
		// else
		else
		{
			// Set the jump
			hasJumped = true;
		}
	}

}
