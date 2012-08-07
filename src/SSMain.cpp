#include "SSMain.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

typedef std::pair<std::string, Level*> lvlPair;

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
		// Call the Graphics init method
		Engine.Graphics->init(1280, 800, "Sandstorms");

      player = new Player(TGA::Vector2D(0, 570));

      makeLevels();

	   healthMana = new HealthManaElement();

      currLevel = "oasis";
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
      std::vector<Platform*> platforms = levels[currLevel]->getPlatforms();
      std::vector<Artifact*> artifacts = levels[currLevel]->getArtifacts();
      std::vector<Projectile*> projectiles = TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->getProjectiles();

      for (std::vector<Platform*>::iterator i = platforms.begin();
         i < platforms.end(); i++)
      {
         TGA::Collision::handleCollisions((*player), *(*i));
      }

      for (std::vector<Artifact*>::iterator i = artifacts.begin();
         i < artifacts.end(); i++)
      {
         TGA::Collision::handleCollisions((*player), *(*i));
      }

      for (std::vector<Projectile*>::iterator i = projectiles.begin();
         i < projectiles.end(); i++)
      {
         TGA::Collision::handleCollisions((*player), *(*i));

         for (std::vector<Platform*>::iterator j = platforms.begin();
            j < platforms.end(); j++)
         {
            TGA::Collision::handleCollisions(*(*j), *(*i));
         }
      }

		// Update the AnimationManager
		Engine.Animations->updateAll();

		// Update the Player
      player->update();

      Engine.GameCamera->setPosition(static_cast<float>(player->getPosition().getX()) - SCREEN_WIDTH / 2, 0);

      if (Engine.GameCamera->getX() < 0)
      {
         Engine.GameCamera->setPosition(0, Engine.GameCamera->getY());
      }

      if (Engine.GameCamera->getX() > levels[currLevel]->getRightBound() - SCREEN_WIDTH)
      {
         Engine.GameCamera->setPosition(static_cast<float>(levels[currLevel]->getRightBound() - SCREEN_WIDTH), Engine.GameCamera->getY());
      }

      healthMana->update(player->getHealthPercent(), player->getManaPercent());

      TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->update();
	}

	void SSMain::render(float interpolation)
	{
		// Draw the background
      levels[currLevel]->draw();

		// Draw all Animations
		player->draw(interpolation);

      healthMana->draw();

      TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->draw();

		// Call Graphics Swap Buffers
		Engine.Graphics->swapBuffers();
	}

   void SSMain::generatePlatforms( Level* lvl, std::string platformTex, int platWidth, int platHeight )
   {
      // TODO: Make this smarter?
      
      std::vector<Platform*> platforms;
      Platform* platform;
      TGA::BoundingBox bounds;
      std::vector<Platform*>::iterator currPlatform;

      double xPos, yPos;
      bool platformCreated;
      int attempts;
      int rightBound = lvl->getRightBound();

      for (int i = 0; i < rightBound / 460; i++) // 460 comes from experimentation
      {
         platformCreated = false;
         attempts = 0;

         while (!platformCreated && attempts < 300)
         {
            xPos = randFloat(100, static_cast<float>(rightBound - platWidth));
            yPos = randFloat(200, 660);

            currPlatform = platforms.begin();
            for (; currPlatform < platforms.end(); currPlatform++)
            {
               bounds = (*currPlatform)->getBounds();

               if (abs(bounds.getX() - xPos) < platWidth * 2
                  && (abs(bounds.getY() - yPos < platHeight * 6)))
               {
                  break;
               }
            }

            if (currPlatform == platforms.end())
            {
               platform = new Platform(platformTex, static_cast<int>(xPos), static_cast<int>(yPos), 
                  platWidth, platHeight);
               lvl->addPlatform(platform);
               platforms.push_back(platform);

               platformCreated = true;
            }

            if (attempts == 299)
            {
               std::cout << "Too many attempts\n";
            }

            attempts++;
         }
      }

      std::cout << platforms.size();
   }

   void SSMain::makeLevels()
   {
      std::vector<Platform*> platforms;
      std::vector<Layer*> layers;
      std::vector<Artifact*> artifacts;

      const int oasis_width = 15000;

      // Boundary platforms, invisible textures
      platforms.push_back(new Platform("../resources/level/invis.png", -40, 750, oasis_width, 20));
      platforms.push_back(new Platform("../resources/level/invis.png", -10, -100, 10, 900));
      platforms.push_back(new Platform("../resources/level/invis.png", oasis_width, -100, 10, 900));

      layers.push_back(new Layer("../resources/level/oasis.png", 0.94, false));
      layers.push_back(new Layer("../resources/level/oasis_ground.png", 0.0, true));

      artifacts.push_back(new Artifact("../resources/artifacts/smiley.png", TGA::Vector2D(100, 400)));

      levels.insert(levels.begin(), lvlPair("oasis", new Level(oasis_width, layers, platforms, artifacts)));

      generatePlatforms(levels["oasis"], "../resources/level/large_oasis.png", 125, 37);
   }

}