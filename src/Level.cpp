/**
 * @file Level.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Level.h"

Level::Level(int rightBound, std::vector<Layer*> layers, std::vector<Platform*> platforms /*= std::vector<Platform*>()*/, std::vector<Artifact*> artifacts /*= std::vector<Artifact*>()*/ )
   : layers(layers)
   , platforms(platforms)
   , artifacts(artifacts)
{
   this->rightBound = rightBound;
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

   for(std::vector<Artifact*>::iterator i = artifacts.begin(); i < artifacts.end(); i++)
   {
      (*i)->draw();
   }
}

std::vector<Platform*> Level::getPlatforms()
{
   return platforms;
}

int Level::getRightBound()
{
   return rightBound;
}
