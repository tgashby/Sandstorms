#pragma once

#include <ProjIncludes.h>
#include "Character.h"

namespace Sandstorms
{
	class Player : Character
	{
	public:
		Player(void);
		~Player(void);

		virtual void initAttributes(int level);

		virtual void moveToward(Character& who);

		virtual void attack(Character& who);

		void changeAttack(int attackNum);

		void jump();

		void setSingleJumped(bool val);
		void setDoubleJumped(bool val);

	private:
		bool hasJumped, hasDoubleJumped;
		Uint64 lastJump;
	};
}

