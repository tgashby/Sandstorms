#include "Player.h"

namespace Sandstorms
{
	Player::Player() : Character("resources/player.png", 1337)
	{
		// Set hasJumped to false
		// Set hasDoubleJumped to false

		// Add animation frames (multi-line)
		// ....
		// ....
	}

	Player::~Player(void) {}

	void Player::initAttributes(int level)
	{
		// Set health to 250
		// Set speed to 5? (I dunno)
	}

	void Player::attack(Character& who)
	{
		// IF the current is a MeleeAttack
			// IF the attack's range is within the who's bounds
				// Damage that Character with the attack's strength
		// ELSE (it's a ranged attack)
			// Send the ranged attack in the direction of mouse
	}

	void Player::changeAttack(int attackNum)
	{
		// Change the current attack to attackNum
	}

	void Player::jump()
	{
		// If the player has not double jumped
			// Add 10 to the player's y value
			// Add 10 to the player's y velocity

		// If the player has jumped
			// Set the double jump
		// else
			// Set the jump
	}

	void Player::setSingleJumped(bool val)
	{
		// Set hasJumped
	}

	void Player::setDoubleJumped(bool val)
	{
		// Set hasDoubleJumped
	}

}
