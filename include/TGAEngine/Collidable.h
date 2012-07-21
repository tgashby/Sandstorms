/**
 * @file Collidable.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include "BoundingBox.h"

namespace TGA
{
   /**
    * @class Collidable
    *
    * @brief "Interface" to attach to anything that can be collided with.
    *
    */
   class Collidable 
   {
   public:
      Collidable(BoundingBox b);

      /**
      * handleCollision
      *
      * Updates the collidable entity based on what it collided with.
      * @param Collidable collidedWith - the collidable entity collided with
      */
      virtual void handleCollision (Collidable& collidedWith) = 0;

      /**
      * getBounds
      *
      * Returns the boundaries of this collidable.
      * @return TGA::BoundingBox - the bounds of the collidable
      */
      BoundingBox getBounds ();

   protected:
      BoundingBox bounds;
   };
}
