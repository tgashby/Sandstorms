/**
 * @file Consumable.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <Collidable.h>
#include <Texture.h>
#include <Vector2D.h>

/**
 * @class Consumable
 *
 * @brief Anything that the player will pick up.
 *
 */
class Consumable : public TGA::Collidable
{
public:
   Consumable(std::string texName, TGA::Vector2D position);

  /**
  * handleCollision
  *
  * Deal with collisions with the player.
  * @param collidedWith - the other object collided with
  */
  virtual void handleCollision (TGA::Collidable& collidedWith) = 0;

  /**
  * draw
  *
  * Draws the Consumable.
  */
  virtual void draw ();
protected:
   TGA::Vector2D position;
   TGA::Texture* texture;
   bool used;
};

