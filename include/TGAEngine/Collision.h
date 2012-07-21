/**
 * @file Collision.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include "BoundingBox.h"
#include "Collidable.h"

namespace TGA
{
   /**
    * @class Collision
    *
    * @brief Collection of static methods to check for collisions.
    *
    */
   class Collision 
   {
   public:
      /**
      * checkCollision
      *
      * Determine if two bounding boxes are colliding.
      * @param TGA::BoundingBox b1 - the first box
      * @param TGA::BoundingBox b2 - the second box
      * @return bool - true if the boxes are colliding (overlapping)
      */
      static bool checkCollision (BoundingBox b1, BoundingBox b2);

      /**
      * handleCollisions
      *
      * Determines if two Collidable entities are in fact colliding.
      * Calls each entity's handleCollision method.
      * @param TGA::Collidable c1 - the first entity
      * @param TGA::Collidable c2 - the second entity
      */
      static void handleCollisions (Collidable& c1, Collidable& c2);
   };
}


