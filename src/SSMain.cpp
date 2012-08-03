#include "SSMain.h"

const int RIGHT_BOUND = 5000;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

float randFloat(float a, float b)
{
   return ((b-a)*((float)rand()/RAND_MAX))+a;
}

namespace Sandstorms
{
	SSMain::SSMain(void)
	{
      srand((int)time(NULL));
	}
	
	
	SSMain::~SSMain(void)
	{
	}

	void SSMain::init()
	{
      std::vector<Platform*> platforms;
      std::vector<Layer*> layers;
      std::vector<Artifact*> artifacts;

		// Call the Graphics init method
		Engine.Graphics->init(1280, 800, "Sandstorms");

      player = new Player(TGA::Vector2D(0, 570));

      // Ground platform, invisible texture
      platforms.push_back(new Platform("../resources/level/invis.png", -40, 750, 5500, 20));

      layers.push_back(new Layer("../resources/level/oasis.png", 0.9, false));
      layers.push_back(new Layer("../resources/level/oasis_ground.png", 0.0, true));

      level = new Level(layers, platforms, artifacts);

      generatePlatforms(level, "../resources/level/large_oasis.png", 125, 37);

	   healthMana = new HealthManaElement();
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
            running = handleEvents();
            if (!running)
            {
               break;
            }

            updateGame();

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

	bool SSMain::handleEvents()
	{
		// Update the Input
		bool stillGoing = Engine.Input->update();

      if (stillGoing)
      {
         stillGoing = !Engine.Input->keyDown(TGA::key_ESC);
      }

		return stillGoing;
	}

	void SSMain::updateGame()
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

      Engine.GameCamera->setPosition(player->getPosition().getX() - SCREEN_WIDTH / 2, 0);

      if (Engine.GameCamera->getX() < 0)
      {
         Engine.GameCamera->setPosition(0, Engine.GameCamera->getY());
      }

      if (Engine.GameCamera->getX() > RIGHT_BOUND - SCREEN_WIDTH)
      {
         Engine.GameCamera->setPosition(RIGHT_BOUND - SCREEN_WIDTH, Engine.GameCamera->getY());
      }

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

   void SSMain::generatePlatforms( Level* lvl, std::string platformTex, int platWidth, int platHeight )
   {
      // TODO: Make this actually smart.

      double xPos, yPos;

      for (int i = 0; i < 40; i++)
      {
         xPos = randFloat(0, RIGHT_BOUND - platWidth);
         yPos = randFloat(0, 510);

         lvl->addPlatform(platformTex, xPos, yPos, platWidth, platHeight);
      }
   }
}