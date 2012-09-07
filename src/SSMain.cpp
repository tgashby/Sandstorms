#include "SSMain.h"
#include <Key.h>
#include <time.h>
#include "Level.h"
#include "Player.h"
#include "HealthManaElement.h"
#include "Artifact.h"
#include "ProjectileFactory.h"
#include "HealthPickup.h"
#include "ManaPickup.h"
#include "Layer.h"
#include "Hound.h"
#include "Warrior.h"
#include "Caster.h"
#include "AttackManager.h"
#include "MenuState.h"
#include "StoryState.h"
#include "WinState.h"
#include "LoseState.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int HEALTH_PICKUP_AMT = 60;
const int MANA_PICKUP_AMT = 50;

typedef std::pair<std::string, Level*> lvlPair;

float randFloat(float a, float b)
{
   return ((b-a)*((float)rand()/RAND_MAX))+a;
}

bool sortPlatforms(Platform* p1, Platform* p2)
{
   return *p1 < *p2;
}

SSMain::SSMain()
{
   srand((int)time(NULL));
   TGA::Music* music;

   Engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   music = new TGA::Music("resources/sound/oasis_level.ogg");
   Engine->Sounds->addMusic(music, "oasis_music");

   music = new TGA::Music("resources/sound/city_level.ogg");
   Engine->Sounds->addMusic(music, "city_music");
}

SSMain::~SSMain()
{
}

void SSMain::init()
{
   // Call the Graphics init method
   Engine->Graphics->init(1280, 800, "Sandstorms");

   MenuState menu;
   StoryState backstory("resources/ui/backstory.png", 6);

   player = new Player(TGA::Vector2D(0, 570));

   makeLevels();

   healthMana = new HealthManaElement();

   menu.draw();

   while (menu.update());

   backstory.draw();

   while (backstory.update());

   startGame();
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
   Engine->Graphics->shutDown();
}

void SSMain::startGame()
{
   Engine->Sounds->pauseMusic("oasis_music");

   StoryState oasisObjective("resources/ui/oasis_objective.png", 2);

   player->reset();

   currLevel = "oasis";

   oasisObjective.draw();

   while (oasisObjective.update());

   Engine->Sounds->playMusic("oasis_music", -1);
}

bool SSMain::handleEvents()
{
   // Update the Input
   bool stillGoing = Engine->Input->update();

   if (stillGoing)
   {
      stillGoing = !Engine->Input->keyDown(TGA::key_ESC);
   }

   return stillGoing;
}

void SSMain::updateGame()
{
   std::vector<Platform*> platforms = levels[currLevel]->getPlatforms();
   std::vector<Consumable*> consumables = levels[currLevel]->getConsumables();
   std::vector<Projectile*> projectiles = TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->getProjectiles();
   std::vector<Attack*> attacks = TGA::Singleton<AttackManager>::GetSingletonPtr()->getAttacks();

   // Level.update handles player<->platform, player<->consumable, and projectile<->platform, player<->enemy, attack<->enemy collision
   levels[currLevel]->update(player);

   for (std::vector<Projectile*>::iterator i = projectiles.begin();
      i < projectiles.end(); i++)
   {
      TGA::Collision::handleCollisions((*player), *(*i));
   }

   for (std::vector<Attack*>::iterator i = attacks.begin(); i < attacks.end(); i++)
   {
      TGA::Collision::handleCollisions((*player), *(*i));
   }

   Engine->Animations->updateAll();

   player->update();

   // Scroll with player
   Engine->GameCamera->setPosition(static_cast<float>(player->getPosition().getX()) - SCREEN_WIDTH / 2, 0);

   if (Engine->GameCamera->getX() < 0)
   {
      Engine->GameCamera->setPosition(0, Engine->GameCamera->getY());
   }

   if (Engine->GameCamera->getX() > levels[currLevel]->getRightBound() - SCREEN_WIDTH)
   {
      Engine->GameCamera->setPosition(static_cast<float>(levels[currLevel]->getRightBound() - SCREEN_WIDTH), Engine->GameCamera->getY());
   }

   healthMana->update(player->getHealthPercent(), player->getManaPercent());

   TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->update();
   TGA::Singleton<AttackManager>::GetSingletonPtr()->UpdateAttacks();

   if (player->getArtifactCount() == 1 && currLevel.compare("city") != 0)
   {
      Engine->Sounds->pauseMusic("oasis_music");
      Engine->Sounds->pauseAllSounds();

      StoryState cityObjective("resources/ui/city_objective.png", 3);

      Engine->GameCamera->setPosition(0, 0);

      cityObjective.draw();

      while (cityObjective.update());

      currLevel = "city";

      Engine->Sounds->playMusic("city_music", -1);

      player->reset();
   }
   else if (player->getArtifactCount() == 1 && currLevel.compare("city") == 0)
   {
      bool playingAgain;

      Engine->Sounds->pauseMusic("city_music");
      Engine->Sounds->pauseAllSounds();

      WinState win(playingAgain);

      Engine->GameCamera->setPosition(0, 0);

      win.draw();

      while (win.update());

      if (playingAgain)
      {
         levels.clear();
         makeLevels();
         startGame();
         run();
      }
      else
      {
         exit(EXIT_SUCCESS);
      }
   }

   if (player->getHealthPercent() <= 0)
   {
      bool playingAgain;

      Engine->Sounds->pauseMusic("oasis_music");
      Engine->Sounds->pauseMusic("city_music");
      Engine->Sounds->pauseAllSounds();

      LoseState lose(playingAgain);

      Engine->GameCamera->setPosition(0, 0);

      lose.draw();

      while (lose.update());

      if (playingAgain)
      {
         levels.clear();
         makeLevels();
         startGame();
         run();
      }
      else
      {
         exit(EXIT_SUCCESS);
      }
   }

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
   Engine->Graphics->swapBuffers();
}

void SSMain::generatePlatforms( Level* lvl, std::string platformTex, int platWidth, int platHeight )
{
   // TODO: Make this smarter?

   std::vector<Platform*> platforms;
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
         xPos = randFloat(1280, static_cast<float>(rightBound - platWidth));
         yPos = randFloat(260, 450);

         assert(xPos > 100 && xPos < rightBound - platWidth + 1);

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
            platforms.push_back(new Platform(platformTex, static_cast<int>(xPos), static_cast<int>(yPos), platWidth, platHeight));

            platformCreated = true;
         }

         if (attempts == 299)
         {
            std::cout << "Too many attempts\n";
         }

         attempts++;
      }
   }

   // Sort the platforms so that Consumables can be placed better
   sort(platforms.begin(), platforms.end(), sortPlatforms);

   for(std::vector<Platform*>::iterator i = platforms.begin();
      i < platforms.end(); i++)
   {
      lvl->addPlatform(*i);
   }
}

void SSMain::makeLevels()
{
   std::vector<Platform*> platforms;
   std::vector<Layer*> layers;

   const int oasis_width = 15000;
   const int city_width = 15000;

   // Oasis
   // Boundary platforms, invisible textures
   platforms.push_back(new Platform("resources/level/invis.png", -40, 750, oasis_width, 20));
   platforms.push_back(new Platform("resources/level/invis.png", -10, -100, 10, 900));
   platforms.push_back(new Platform("resources/level/invis.png", oasis_width, -100, 10, 900));

   // Oasis Layers
   layers.push_back(new Layer("resources/level/oasis.png", 0.94, false));
   layers.push_back(new Layer("resources/level/ground.png", 0.0, true));
   layers.push_back(new Layer("resources/level/instructions.png", 0.0, false));

   levels.insert(levels.begin(), lvlPair("oasis", new Level(oasis_width, layers, platforms)));

   generatePlatforms(levels["oasis"], "resources/level/large_oasis.png", 125, 37);
   placeConsumables(levels["oasis"], 3, 3, 1, "resources/artifacts/key_artifact.png", 50);
   placeEnemies(levels["oasis"], 4, 2, 2, 2);

   platforms.clear();
   layers.clear();

   assert(platforms.size() == 0);
   assert(layers.size() == 0);

   // City
   // Boundary platforms, invisible textures
   platforms.push_back(new Platform("resources/level/invis.png", -40, 750, city_width, 20));
   platforms.push_back(new Platform("resources/level/invis.png", -10, -100, 10, 900));
   platforms.push_back(new Platform("resources/level/invis.png", city_width, -100, 10, 900));

   // City Layers
   layers.push_back(new Layer("resources/level/city.png", 0.94, false));
   layers.push_back(new Layer("resources/level/ground.png", 0.0, true));

   levels.insert(levels.begin(), lvlPair("city", new Level(city_width, layers, platforms)));

   generatePlatforms(levels["city"], "resources/level/large_city.png", 123, 37);
   placeConsumables(levels["city"], 6, 5, 1, "resources/artifacts/crown_artifact.png", 50);
   placeEnemies(levels["city"], 6, 3, 3, 4);
}

void SSMain::placeConsumables(Level *lvl, int numHPickups, int numMPickups, int numArtifacts, std::string artifactTex, int artifactHeight)
{
   const int H_PICKUP_HEIGHT = 50, M_PICKUP_HEIGHT = 61;

   std::vector<Platform*> platforms = lvl->getPlatforms();

   std::vector<Platform*>::size_type middle = platforms.size() / 2, end = platforms.size();

   int hStep = (end - middle) / numHPickups,
      mStep = (end - middle) / numMPickups,
      aStep = (end - middle) / numArtifacts;

   unsigned int ndx;
   int xVal, yVal;

   // Place health pickups starting from the middle of the level with some
   for (int i = 0; i < numHPickups; i++)
   {
      ndx = middle + (hStep * i) + (rand() % 4);
      ndx = ndx > end - 1 ? end - 1 : ndx;
      xVal = platforms[ndx]->getBounds().getX();
      yVal = platforms[ndx]->getBounds().getY() - H_PICKUP_HEIGHT;
      lvl->addConsumable(new HealthPickup(HEALTH_PICKUP_AMT, TGA::Vector2D(xVal, yVal)));
   }

   // Place mana pickups starting from the middle of the level
   for (int i = 0; i < numMPickups; i++)
   {
      ndx = middle + (mStep * i) + (rand() % 4);
      ndx = ndx > end - 1 ? end - 1 : ndx;
      xVal = platforms[ndx]->getBounds().getX() + platforms[ndx]->getBounds().getWidth() / 2;
      yVal = platforms[ndx]->getBounds().getY() - M_PICKUP_HEIGHT;
      lvl->addConsumable(new ManaPickup(MANA_PICKUP_AMT, TGA::Vector2D(xVal, yVal)));
   }

   // Place artifacts starting from the END
   for (int i = 0; i < numArtifacts; i++)
   {
      ndx = (end - 1) - (aStep * i) - (rand() % 4);
      ndx = ndx > end - 1 ? end - 1 : ndx;
      xVal = platforms[ndx]->getBounds().getX() + platforms[ndx]->getBounds().getWidth() - 10;
      yVal = platforms[ndx]->getBounds().getY() - artifactHeight;
      lvl->addConsumable(new Artifact(artifactTex, TGA::Vector2D(xVal, yVal)));
   }
}

void SSMain::placeEnemies(Level *lvl, int numHounds, int numWarriors, int numCasters, int stationaryCasters)
{
   const int HOUND_HEIGHT = 75, CASTER_HEIGHT = 200, WARRIOR_HEIGHT = 266;

   int xVal, yVal,
      rightBound = lvl->getRightBound();

   std::vector<int> allXVals;

   // Stuff for stationary casters
   std::vector<Platform*> platforms = lvl->getPlatforms();

   std::vector<Platform*>::size_type quarter = platforms.size() / 4, end = platforms.size();

   int casterStep = (end - quarter) / stationaryCasters;

   unsigned int ndx;
   // End stuff for stationary casters

   for (int i = 0; i < numHounds; i++)
   {
      xVal = (rand() % rightBound);

      while (invalidXVal(allXVals, xVal))
      {
         xVal = (rand() % rightBound);
      }

      allXVals.push_back(xVal);

      yVal = 750 - HOUND_HEIGHT;
      lvl->addEnemy(new Hound(40, TGA::Vector2D(xVal, yVal),
                              TGA::Vector2D(randFloat(-7, -4), 0)));
   }

   for (int i = 0; i < numWarriors; i++)
   {
      xVal = (rand() % rightBound);

      while (invalidXVal(allXVals, xVal))
      {
         xVal = (rand() % rightBound);
      }

      allXVals.push_back(xVal);

      yVal = 750 - WARRIOR_HEIGHT;
      lvl->addEnemy(new Warrior(100, TGA::Vector2D(xVal, yVal),
                                TGA::Vector2D(randFloat(-5, -2), 0)));
   }

   for (int i = 0; i < numCasters; i++)
   {
      xVal = (rand() % rightBound);

      while (invalidXVal(allXVals, xVal))
      {
         xVal = (rand() % rightBound);
      }

      allXVals.push_back(xVal);

      yVal = 750 - CASTER_HEIGHT;
      lvl->addEnemy(new Caster(60, TGA::Vector2D(xVal, yVal),
                               TGA::Vector2D(randFloat(-9, -6), 0)));
   }
   
   allXVals.clear();

   for (int i = 0; i < stationaryCasters; i++)
   {
      ndx = quarter + (casterStep * i) + (rand() % 4);
      
      while (find(allXVals.begin(), allXVals.end(), ndx) != allXVals.end())
      {
         ndx = quarter + (casterStep * i) + (rand() % 4);
      }
      
      allXVals.push_back(ndx);
      
      ndx = ndx > end - 1 ? end - 1 : ndx;
      xVal = platforms[ndx]->getBounds().getX();
      yVal = platforms[ndx]->getBounds().getY() - CASTER_HEIGHT;
      lvl->addEnemy(new Caster(60, TGA::Vector2D(xVal, yVal), TGA::Vector2D(0, 0)));
   }   
}

bool SSMain::invalidXVal( std::vector<int> allXVals, int xVal )
{
   if (xVal < 1280)
   {
      return true;
   }
   
   for (std::vector<int>::iterator i = allXVals.begin(); i < allXVals.end(); i++)
   {
      if (abs(*i - xVal) < 300)
      {
         return true;
      }
   }
   
   return false;
}
