/**
 * @file Projectile.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <Collidable.h>
#include <Vector2D.h>
#include <Texture.h>

/**
 * @class Projectile
 *
 * @brief Represents anything that flies. Spells, weapons, etc
 *
 */
class Projectile : public TGA::Collidable
{
public:
   Projectile(std::string textureName, 
      TGA::BoundingBox bounds, TGA::Vector2D pos, TGA::Vector2D vel);
   ~Projectile(void);

   bool update();
   void draw();

   virtual void handleCollision( Collidable& collidedWith );

private:
   TGA::Vector2D position, velocity;
   TGA::Texture texture;
   bool flipped, collided;
};
