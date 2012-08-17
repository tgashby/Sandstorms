/**
 * @file Level.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Level.h"
#include "Player.h"
#include "ProjectileFactory.h"
#include <Engine.h>
#include <Singleton.h>
#include <Texture.h>
#include <Collidable.h>

Level::Level(int rightBound, std::vector<Layer*> layers, std::vector<Platform*> platforms /*= std::vector<Platform*>()*/, std::vector<Consumable*> consumables /*= std::vector<Artifact*>()*/ )
   : layers(layers)
   , platforms(platforms)
   , consumables(consumables)
{
   this->rightBound = rightBound;
}

void Level::update(Player *player)
{
   std::vector<Projectile*> projectiles = TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->getProjectiles();
   
   for (std::vector<Platform*>::iterator i = platforms.begin();
        i < platforms.end(); i++)
   {
      TGA::Collision::handleCollisions((*player), *(*i));
   }
   
   for (std::vector<Consumable*>::iterator i = consumables.begin();
        i < consumables.end(); i++)
   {
      TGA::Collision::handleCollisions((*player), *(*i));
   }
   
   for (std::vector<Projectile*>::iterator i = projectiles.begin();
        i < projectiles.end(); i++)
   {
      for (std::vector<Platform*>::iterator j = platforms.begin();
           j < platforms.end(); j++)
      {
         TGA::Collision::handleCollisions(*(*j), *(*i));
      }
   }
}

void Level::addLayer( Layer* newLayer )
{
   layers.push_back(newLayer);
}

void Level::addLayer( std::string texStr, double moveRate, bool tiled )
{
   layers.push_back(new Layer(texStr, moveRate, tiled));
}

void Level::addPlatform(Platform* newPlatform)
{
   platforms.push_back(newPlatform);
}

void Level::addPlatform(std::string textureStr, int x, int y, int width, int height)
{
   Platform* platform = new Platform(textureStr, x, y, width, height);

   platforms.push_back(platform);
}

void Level::addConsumable( Consumable* newConsumable )
{
   consumables.push_back(newConsumable);
}

void Level::draw()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   
   for (std::vector<Layer*>::iterator i = layers.begin(); i < layers.end(); i++)
   {
      (*i)->draw(engine->GameCamera->getX());
   }

   for(std::vector<Platform*>::iterator i = platforms.begin(); i < platforms.end(); i++)
   {
      (*i)->draw();
   }

   for(std::vector<Consumable*>::iterator i = consumables.begin(); i < consumables.end(); i++)
   {
      (*i)->draw();
   }
}

std::vector<Platform*> Level::getPlatforms()
{
   return platforms;
}

std::vector<Consumable*> Level::getConsumables()
{
   return consumables;
}

int Level::getRightBound()
{
   return rightBound;
}
