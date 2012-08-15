/**
 * @file Consumable.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Consumable.h"
#include "Player.h"


Consumable::Consumable(std::string texName, TGA::Vector2D position )
   : TGA::Collidable(TGA::BoundingBox(0,0,0,0))
   , position(position)
{
   texture = new TGA::Texture(texName);

   bounds.setX(static_cast<int>(position.getX()));
   bounds.setY(static_cast<int>(position.getY()));
   bounds.setWidth(texture->getWidth());
   bounds.setHeight(texture->getHeight());

   used = false;
}

void Consumable::draw()
{
   if (!used)
   {
      texture->draw(static_cast<float>(position.getX()), static_cast<float>(position.getY()));
   }
}