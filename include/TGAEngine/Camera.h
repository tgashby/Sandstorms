/**
 * @file Camera.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once

#include "ProjIncludes.h"

namespace TGA
{
   /**
    * @class Camera
    *
    * @brief A camera to maintain the viewport of the application
    *
    */
	class Camera
	{
	public:
		/**
		* Camera
		*
		* Initialize the camera to be at the origin.
		*/
		Camera();
		~Camera();

		/**
		* moveOver
		*
		* Moves the camera over by an x and y amount.
      * @warning Assumes the application is set up so that the 
      * upper right is (0,0) and x increases to the right, y increases
      * downward
		* @param xVal - amount in x to move right
		* @param yVal - amount in y to move down
		*/
		void moveOver(float xVal, float yVal);

		/**
		* setPosition
		*
		* Sets the position of the camera.
      * @warning Assumes the application is set up so that the 
      * upper right is (0,0) and x increases to the right, y increases
      * downward
		* @param xPos - the x position of the camera
		* @param yPos - the y position of the camera
		*/
		void setPosition(float xPos, float yPos);

		/**
		* getX
		*
		* Gets the x position of the camera.
		* @return float - the x position of the camera
		*/
		float getX();

		/**
		* getY
		*
		* Gets the y position of the camera.
		* @return float - the y position of the camera
		*/
		float	getY();

	private:
		float xPos, yPos;
	};
}


