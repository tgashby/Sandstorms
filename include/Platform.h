/**
 * @file Platform.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <BoundingBox.h>
#include <Collidable.h>
#include <Texture.h>
#include <string>

/**
   * @class Platform
   *
   * @brief Represents a single platform in a level.
   *
   */
class Platform : public TGA::Collidable
{
public:
   /**
   * Platform
   *
   * Create a platform with a the path to its texture and
   * its bounds.
   * @param std::string textureStr - the path to a texture
   * @param TGA::BoundingBox bounds - 
   * @return  -
   */
   Platform (std::string textureStr, TGA::BoundingBox bounds);

   /**
   * Platform
   *
   * 
   * @param std::string textureStr - 
   * @param int x - 
   * @param int y - 
   * @param int width - 
   * @param int height - 
   * @return  -
   */
   Platform (std::string textureStr, int x, int y, int width, int height);
   
   /**
   * draw
   *
   * Draws the platform using its texture.
   */
   void draw();

   /**
   * handleCollision
   *
   * Update the state of the platform based on what it collided with.
   * @param TGA::Collidable collidedWith - the entity collided with
   */
   virtual void handleCollision (TGA::Collidable collidedWith);

private:
   TGA::Texture texture;
};
