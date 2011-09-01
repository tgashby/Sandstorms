#pragma once

#include <App.h>
#include <Key.h>
#include <Engine.h>

#include "Player.h"

namespace Sandstorms
{
	class SSMain : TGA::App
	{
	public:
		SSMain(void);
		~SSMain(void);

		virtual void init();

		virtual void run();

		virtual void shutDown();

	private:
		bool processEvents();
		void processLogic();
		void render();

		TGA::Engine theEngine;
		Player player;
	};
}
