/**
 * @file BoundingBox.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <SDL.h>

namespace TGA
{
   /**
    * @class BoundingBox
    *
    * @brief Represents the boundaries of an entity.
    *
    * Really just wraps an SDL_Rect.
    */
   class BoundingBox 
   {

   friend class Collision;

   public:
      /**
      * BoundingBox
      *
      * Create a bounding box with the given dimensions.
      * @param x - the x position of the box
      * @param y - the y position of the box
      * @param width - the width of the box
      * @param height - the height of the box 
      */
      BoundingBox(int x, int y, int width, int height);

      /**
      * BoundingBox
      *
      * Default constructor, 0's for all values.
      */
      BoundingBox();

      /**
      * getX
      *
      * Gets the box's x value.
      * @return int - the x value
      */
      int getX ();

      /**
      * getY
      *
      * Gets the box's y value.
      * @return int - the y value
      */
      int getY ();

      /**
      * getWidth
      *
      * Get the box's width.
      * @return int - the box width
      */
      int getWidth ();

      /**
      * getHeight
      *
      * Gets the box's height.
      * @return int - the box height
      */
      int getHeight ();

      /**
      * setX
      *
      * Set the box's x position.
      * @param newX - the new x position
      */
      void setX (int newX);

      /**
      * setY
      *
      * Sets the box's y position.
      * @param newY - the new y position
      */
      void setY (int newY);

      /**
      * setX
      *
      * Set the box's width.
      * @param newWidth - the new width
      */
      void setWidth (int newWidth);

      /**
      * setY
      *
      * Sets the box's height.
      * @param newHeight - the new height
      */
      void setHeight (int newHeight);

   private:
      SDL_Rect bounds;
   };
}