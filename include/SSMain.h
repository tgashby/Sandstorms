#pragma once

#include <Key.h>
#include <Engine.h>

#include "Player.h"

namespace Sandstorms
{
	class SSMain
	{
	public:
		SSMain(void);
		~SSMain(void);

		void init();

		void run();

		void shutDown();

	private:
		bool processEvents();
		void processLogic();
		void render();

		TGA::Engine theEngine;
		Player player;
	};
}
