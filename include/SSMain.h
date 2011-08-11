#pragma once
#include <App.h>
#include <Engine.h>

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
		void processEvents();
		void processLogic();
		void render();

		Player player;
	};
}
