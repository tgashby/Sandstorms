/**
 * @file Platform.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#include "Platform.h"
#include "Player.h"

Platform::Platform(std::string textureStr, TGA::BoundingBox bounds)
   : TGA::Collidable(bounds)
{
   if (!texture.loadTexture(textureStr))
   {
      std::cerr << "Failed to load level texture: " << textureStr << "\n";
   }
}

Platform::Platform(std::string textureStr, int x, int y, int width, int height)
   : TGA::Collidable(TGA::BoundingBox(x, y, width, height))
{
   if (!texture.loadTexture(textureStr))
   {
      std::cerr << "Failed to load level texture: " << textureStr << "\n";
   }
}

void Platform::draw()
{
   texture.draw((float)this->bounds.getX(), (float)this->bounds.getY());
}

void Platform::handleCollision(TGA::Collidable& collidedWith)
{
   if (typeid(collidedWith) == typeid(Player))
   {
   }
   
   if (typeid(collidedWith) == typeid(Platform))
   {
      std::cerr << "Overlapping platforms." << "\n";
   }
}

bool Platform::operator<(Platform& p2)
{
   return getBounds().getX() < p2.getBounds().getX();
}