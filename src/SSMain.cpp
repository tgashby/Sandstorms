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

      platforms.push_back(new Platform("../resources/level/large_oasis.png", 200, 500, 125, 37));
      platforms.push_back(new Platform("../resources/level/large_oasis.png", 650, 250, 125, 37));
      platforms.push_back(new Platform("../resources/level/platform.png", -40, 800, 1360, 20));

      level = new Level("../resources/level/oasis.png", 1.0, false, std::vector<Artifact*>(), platforms);
	   healthMana = new HealthManaElement("../resources/ui/healthManaContainer.png");
   }

	void SSMain::run()
	{
		// Create a bool for whether or not the game is running
		bool running = true;

      const int TICKS_PER_SECOND = 60;
      const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
      const int MAX_FRAMESKIP = 5;

      Uint32 next_game_tick = TGA::Timer::getTicks();
      int loops;
      float interpolation;

      while (running) {

         loops = 0;
         while (TGA::Timer::getTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
            running = processEvents();
            if (!running)
            {
               break;
            }

            processLogic();

            next_game_tick += SKIP_TICKS;
            loops++;
         }

         interpolation = float(TGA::Timer::getTicks() + SKIP_TICKS - next_game_tick)
            / float(SKIP_TICKS);
         
         render(interpolation);
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

	void SSMain::processLogic()
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
      player->update();
      
      healthMana->update(player->getHealthPercent(), player->getManaPercent());
	}

	void SSMain::render(float interpolation)
	{
		// Draw the background
      level->draw();

		// Draw all Animations
		player->draw(interpolation);

      healthMana->draw();

		// Call Graphics Swap Buffers
		Engine.Graphics->swapBuffers();
	}
}
