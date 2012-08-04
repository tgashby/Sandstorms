#pragma once

#include <Key.h>
#include <Engine.h>
#include <time.h>
#include "Level.h"
#include "Player.h"
#include "HealthManaElement.h"
#include "Artifact.h"

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
		bool handleEvents();
		void updateGame();
		void render(float interpolation);
      void generatePlatforms( Level* lvl, std::string platformTex, int platWidth, int platHeight );
      void makeLevels();
      TGA::Engine Engine;
      std::map<std::string, Level*> levels;
      std::string currLevel;
		Player* player;
      HealthManaElement* healthMana;
	};
}
