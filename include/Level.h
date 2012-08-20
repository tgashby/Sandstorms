/**
 * @file Level.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */
#pragma once
#include <string>
#include <vector>

class Player;
class Layer;
class Platform;
class Consumable;
class Enemy;

/**
 * @class Level
 *
 * @brief Represents a single level, complete with platforms.
 *
 */
class Level
{
public:
   /**
    * Level
    *
    * Creates a new Level with the specified background texture.
    * @param std::string backgroundTex - path to the texture file
    * @param moveRate - how many pixels the camera must move before the level moves one, 0 for a stationary background
    * @param bool tiled - whether or not the background should be tiled as we progress
    * @param artifacts - the artifacts in the level
    * @param std::vector<Platform * > platforms - a collection of platforms in the level
    */
   Level (int rightBound, std::vector<Layer*> layers,
          std::vector<Platform*> platforms = std::vector<Platform*>(),
          std::vector<Consumable*> artifacts = std::vector<Consumable*>());
   
   void update(Player* player);
   
   /**
    * addLayer
    *
    * Add a new layer to the level
    * @param newLayer - the layer to add
    */
   void addLayer (Layer* newLayer);
   
   /**
    * addPlatform
    *
    * Add a platform to the level.
    * @param Platform * newPlatform - the platform to add to the level
    */
   void addPlatform (Platform* newPlatform);
   
   /**
    * addConsumable
    *
    * Add a Consumable to the level.
    * @param newConsumable - the new consumable
    */
   void addConsumable (Consumable* newConsumable);
   
   /**
    * addEnemy
    *
    * Adds an enemy to the level.
    * @param newEnemy - the new enemy
    */
   void addEnemy (Enemy* newEnemy);
   
   /**
    * draw
    *
    * Draw the background and all platforms.
    */
   void draw();
   
   std::vector<Platform*> getPlatforms();
   
   std::vector<Consumable*> getConsumables();
   
   int getRightBound();
   
private:
   std::vector<Layer*> layers;
   std::vector<Platform*> platforms;
   std::vector<Consumable*> consumables;
   std::vector<Enemy*> enemies;
   int rightBound;
};

