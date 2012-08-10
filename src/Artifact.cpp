/**
 * @file Artifact.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Artifact.h"
#include "Player.h"


Artifact::Artifact( std::string fileName, TGA::Vector2D position )
   : TGA::Collidable(TGA::BoundingBox(0,0,0,0))
   , position(position)
{
   texture = new TGA::Texture(fileName);

   bounds.setX(static_cast<int>(position.getX()));
   bounds.setY(static_cast<int>(position.getY()));
   bounds.setWidth(texture->getWidth());
   bounds.setHeight(texture->getHeight());

   collected = false;
}

void Artifact::draw()
{
   if (!collected)
   {
      texture->draw(static_cast<float>(position.getX()), static_cast<float>(position.getY()));
   }
   else
   {
      TGA::Camera* camera = TGA::Singleton<TGA::Camera>::GetSingletonPtr();

      texture->draw(camera->getX() + (1270 - texture->getWidth()), 10);
   }
}

void Artifact::handleCollision( TGA::Collidable& collidedWith )
{
   if (typeid(collidedWith) == typeid(Player))
   {
      collected = true;
      bounds.setX(-1);
      bounds.setY(-1);
   }
}

void Artifact::setPosition(double xPos, double yPos)
{
   position.setX(xPos);
   position.setY(yPos);
}