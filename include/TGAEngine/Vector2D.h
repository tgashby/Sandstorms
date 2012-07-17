/**
 * @file Vector2D.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once

namespace TGA
{
   /**
    * @class Vector2D
    *
    * @brief Represents a 2 dimensional math vector
    *
    * Vector2D is the usual vector class complete with vector operations.
    */
	class Vector2D
	{
	public:
		/**
		* Vector2D
		*
		* Creates a Vector2D
		* @param float x - the x component of the vector
		* @param float y - the y component of the vector
		*/
		Vector2D(float x, float y);
		~Vector2D();

     /**
      * operator+=
      *
      * Add a vector to the current vector.
      * @param const Vector2D - the right hand side
      * @return Vector2D& - reference to the new vector
      */
      Vector2D& operator+=(const Vector2D);

		/**
		* operator+
		*
      * Adds two vectors.
      * @param Vector2D - the right hand side of the addition
      * @return TGA::Vector2D - the new Vector2D that is the result
		*/
		Vector2D operator+(Vector2D);
      
      /**
      * operator-=
      *
      * Subtract a vector to the current vector.
      * @param const Vector2D - the right hand side
      * @return Vector2D& - reference to the new vector
      */
      Vector2D& operator-=(const Vector2D);

		/**
		* operator-
		*
		* Subtracts two vectors.
		* @param Vector2D - the right hand side of the subtraction
		* @return TGA::Vector2D - the new Vector2D that is the result
		*/
		Vector2D operator-(Vector2D);

		/**
		* scalarProduct
		*
		* Calculates the scalar product given a scalar.
		* @param int  - the scalar to multiply by
		* @return TGA::Vector2D - the resultant vector
		*/
		Vector2D scalarProduct(int);

		/**
		* normalize
		*
		* Normalizes the vector and returns a new one.
		* @return TGA::Vector2D - the new, normalized, vector
		*/
		Vector2D normalize();

		/**
		* dotProduct
		*
		* Calculates the dot product with another vector.
		* @param Vector2D - the vector to dot with
		* @return float - the dot product
		*/
		float dotProduct(Vector2D);

		/**
		* length
		*
		* Returns the length of the vector.
		* @return float - the length
		*/
		float length();

		/**
		* distanceFrom
		*
		* Gets the distance from the given "point" to another "point".
		* @param Vector2D - the point to calculate distance from
		* @return float - the distance
		*/
		float distanceFrom(Vector2D);

		/**
		* getX
		*
		* Gets the X component of the vector.
		* @return float - the X component
		*/
		float getX();

		/**
		* getY
		*
		* Gets the Y component of the vector.
		* @return float - the Y component
		*/
		float getY();

      void setX(float x);

      void setY(float y);

	private:
		float x, y;
	};
}
