/**
 * @file Artifact.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#include "Artifact.h"


Artifact::Artifact( std::string fileName, TGA::Vector2D position )
   : Consumable(fileName, position)
{

}

void Artifact::handleCollision( TGA::Collidable& collidedWith )
{

}
