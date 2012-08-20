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
#include "AttackManager.h"
#include "Consumable.h"
#include "Platform.h"
#include "Artifact.h"
#include "Layer.h"
#include "Enemy.h"
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
   std::vector<Attack*> attacks = TGA::Singleton<AttackManager>::GetSingletonPtr()->getAttacks();
   
   for (std::vector<Platform*>::iterator i = platforms.begin();
        i < platforms.end(); i++)
   {
      TGA::Collision::handleCollisions((*player), *(*i));
      
      for (std::vector<Enemy*>::iterator j = enemies.begin(); j < enemies.end(); j++)
      {
         TGA::Collision::handleCollisions(*(*j), *(*i));
      }
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
      
      for (std::vector<Enemy*>::iterator j = enemies.begin(); j < enemies.end(); j++)
      {
         TGA::Collision::handleCollisions(*(*j), *(*i));
      }
   }
   
   for (std::vector<Enemy*>::iterator i = enemies.begin();
        i < enemies.end(); i++)
   {
      TGA::Collision::handleCollisions((*player), *(*i));
      
      for (std::vector<Attack*>::iterator j = attacks.begin(); j < attacks.end(); j++)
      {
         TGA::Collision::handleCollisions(*(*i), *(*j));
      }
   }
   
   std::vector<int> removeNdxs;
   for (std::vector<Enemy*>::size_type i = 0; i < enemies.size(); i++)
   {
      enemies.at(i)->update(player->getPosition());
      if (!enemies.at(i)->isAlive())
      {
         removeNdxs.push_back(i);
      }
   }
   
   for (std::vector<int>::iterator i = removeNdxs.begin(); i < removeNdxs.end(); i++)
   {
      enemies.erase(enemies.begin() + *i);
   }
}

void Level::addLayer( Layer* newLayer )
{
   layers.push_back(newLayer);
}

void Level::addPlatform(Platform* newPlatform)
{
   platforms.push_back(newPlatform);
}

void Level::addConsumable( Consumable* newConsumable )
{
   consumables.push_back(newConsumable);
}

void Level::addEnemy(Enemy* newEnemy)
{
   enemies.push_back(newEnemy);
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
   
   for(std::vector<Enemy*>::iterator i = enemies.begin(); i < enemies.end(); i++)
   {
      (*i)->draw(0);
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
