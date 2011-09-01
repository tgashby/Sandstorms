#pragma once

#include <ProjIncludes.h>
#include "Character.h"

namespace Sandstorms
{
	class Player : public Character
	{
	public:
		Player(std::string texName, int lvl, int xPos = 0, int yPos = 0);
		~Player(void);

		virtual void initAttributes(int level);

		virtual void moveToward(Character& who);

		virtual void attack(Character& who);

		virtual void updatePosition();

		void changeAttack(int attackNum);

		void jump();

	private:
		bool hasJumped, hasDoubleJumped;
		Uint64 lastJump;
	};
}

