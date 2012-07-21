#include "SSMain.h"

namespace Sandstorms
{
	SSMain::SSMain(void)
	{
	}
	
	
	SSMain::~SSMain(void)
	{
	}

	void SSMain::init()
	{
		// Call the Graphics init method
		Engine.Graphics->init(1280, 800, "Sandstorms");

      player = new Player(TGA::Vector2D(600, 200));
      level = new Level("../resources/level/Oasis.jpg", false);
	}

	void SSMain::run()
	{
		// Create a bool for whether or not the game is running
		bool running = true;

      Uint32 lastUpdate = TGA::Timer::getTicks();
      float dt;

		// WHILE running
		while(running)
		{
			// Call processEvents()
			running = processEvents();

         dt = (float)(TGA::Timer::getTicks() - lastUpdate) / 10000;

			// Call processLogic()
			processLogic(dt);

			// Call render()
			render();
		}
	}

	void SSMain::shutDown()
	{
		// Call Graphics shutDown method
		Engine.Graphics->shutDown();
	}

	bool SSMain::processEvents()
	{
		// Update the Input
		bool stillGoing = Engine.Input->update();

		return stillGoing;
	}

	void SSMain::processLogic(float dt)
	{
		// Update the AnimationManager
		Engine.Animations->updateAll();

		// Update the Player
      player->update(dt);
	}

	void SSMain::render()
	{
		// Draw the background
      level->draw();

		// Draw all Animations
		player->draw();

		// Call Graphics Swap Buffers
		Engine.Graphics->swapBuffers();
	}
}
