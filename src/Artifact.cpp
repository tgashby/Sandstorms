/**
 * @file Artifact.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Artifact.h"


Artifact::Artifact( std::string fileName, TGA::Vector2D position )
   : TGA::Collidable(TGA::BoundingBox(0,0,0,0))
   , position(position)
{
   texture = new TGA::Texture(fileName);

   bounds.setX(static_cast<int>(position.getX()));
   bounds.setY(static_cast<int>(position.getY()));
   bounds.setWidth(texture->getWidth());
   bounds.setHeight(texture->getHeight());
}

void Artifact::draw()
{
   texture->draw(static_cast<float>(position.getX()), static_cast<float>(position.getY()));
}

void Artifact::handleCollision( TGA::Collidable& collidedWith )
{

}

void Artifact::setPosition(double xPos, double yPos)
{
   position.setX(xPos);
   position.setY(yPos);
}