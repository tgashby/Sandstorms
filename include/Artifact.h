/**
 * @file Artifact.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <Collidable.h>
#include <Vector2D.h>
#include <Texture.h>
#include "Consumable.h"

/**
 * @class Artifact
 *
 * @brief Important collectibles that are needed
 * to proceed to further levels.
 *
 */
class Artifact : public Consumable
{
public:
  /**
  * Artifact
  *
  * Make a new Artifact from the filename at the given position.
  * @param fileName - the path to the artifact's image
  * @param position - the position of the artifact
  */
  Artifact (std::string fileName, TGA::Vector2D position);

  void draw ();

  /**
  * handleCollision
  *
  * Handle collisions with the player. On colliding with the player,
  * attach to the player and disappear from the previous position.
  * @param collidedWith - the object collided with
  */
  void handleCollision (TGA::Collidable& collidedWith);

  void setPosition(double x, double y);

private:
};

