/**
 * @file Attack.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <Collidable.h>
#include "Character.h"

class Attack : public TGA::Collidable
{
public:
   Attack (int damage, TGA::BoundingBox area, Uint32 duration, TGA::Collidable* originator);
  void update ();
  virtual void handleCollision(TGA::Collidable& collidedWith);

protected:
   int damage;

   // Number of update cycles to exist
   int duration;

   TGA::Collidable* originator;
};

