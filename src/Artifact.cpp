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
   : Consumable(fileName, position)
{
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