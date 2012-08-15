/**
 * @file Attack.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <Collidable.h>

class Attack : public TGA::Collidable
{
public:
  Attack (int damage, TGA::BoundingBox area, Uint32 duration, TGA::Character& originator);
  void update ();
  void handleCollision (TGA::Collidable& collidedWith);

protected:
   int damage;
   TGA::BoundingBox area;

   /// Number of update cycles to exist
   int duration;

   TGA::Character& originator;
};

