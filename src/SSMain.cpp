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

      player = new Player(TGA::Vector2D(0, 570));

      std::vector<Platform*> platforms;

      platforms.push_back(new Platform("../resources/level/platform.png", 200, 500, 100, 20));
      platforms.push_back(new Platform("../resources/level/platform.png", 650, 250, 100, 20));
      platforms.push_back(new Platform("../resources/level/platform.png", -40, 800, 1360, 20));

      level = new Level("../resources/level/Oasis.jpg", false, platforms);
	}

	void SSMain::run()
	{
		// Create a bool for whether or not the game is running
		bool running = true;

      Uint32 lastUpdate = TGA::Timer::getTicks();
      Uint32 now, dt;

		// WHILE running
		while(running)
		{
			// Call processEvents()
			running = processEvents();

         now = TGA::Timer::getTicks();

         dt = now - lastUpdate;

			// Call processLogic()
			processLogic(dt);

         lastUpdate = now;

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

      if (stillGoing)
      {
         stillGoing = !Engine.Input->keyDown(TGA::key_ESC);
      }

		return stillGoing;
	}

	void SSMain::processLogic(Uint32 dt)
	{
      std::vector<Platform*> platforms = level->getPlatforms();

      for (std::vector<Platform*>::iterator i = platforms.begin();
         i < platforms.end(); i++)
      {
         TGA::Collision::handleCollisions((*player), *(*i));
      }

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
