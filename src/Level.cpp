/**
 * @file Level.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Level.h"

Level::Level( std::string backgroundTex, bool tiled, std::vector<Platform*> platforms /*= std::vector<Platform*>()*/ )
{
   if (!background.loadTexture(backgroundTex))
   {
      std::cerr << "Failed to load level texture: " << backgroundTex << "\n";
   }

   this->tiled = tiled;

   this->platforms = platforms;
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
   background.draw(0, 0);

   for(std::vector<Platform*>::iterator i = platforms.begin(); i < platforms.end(); i++)
   {
      (*i)->draw();
   }
}
