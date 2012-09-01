#pragma once

#include <Engine.h>

class Player;
class HealthManaElement;
class Level;

class SSMain
{
public:
	SSMain(void);
	~SSMain(void);
      
	void init();
      
	void run();
      
	void shutDown();
      
private:
   void startGame();
	bool handleEvents();
	void updateGame();
	void render(float interpolation);
   void generatePlatforms( Level* lvl, std::string platformTex, int platWidth, int platHeight );
   void makeLevels();
   void placeConsumables(Level* lvl, int numHPickups, int numMPickups,
                           int numArtifacts, std::string artifactTex,
                           int artifactHeight);
   void placeEnemies(Level* lvl, int numHounds, int numWarriors, int numCasters, int stationaryCasters);
   bool invalidXVal(std::vector<int> allXVals, int xVal);
   TGA::Engine* Engine;
   std::map<std::string, Level*> levels;
   std::string currLevel;
	Player* player;
   HealthManaElement* healthMana;
};
