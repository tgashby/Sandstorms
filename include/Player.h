#pragma once

#include <ProjIncludes.h>
#include "Character.h"

namespace Sandstorms
{
	class Player :
		Character
	{
	public:
		Player(void);
		~Player(void);

	private:
		bool hasJumped, hasDoubleJumped;
		Uint64 lastJump;


	};
}

