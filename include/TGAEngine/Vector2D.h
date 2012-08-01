/**
 * @file Vector2D.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once

#include <ostream>

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
		* @param x - the x component of the vector
		* @param y - the y component of the vector
		*/
		Vector2D(double x, double y);
		~Vector2D();

     /**
      * operator+=
      *
      * Add a vector to the current vector.
      * @param v - the right hand side
      * @return Vector2D& - reference to the new vector
      */
      Vector2D& operator+=(const Vector2D v);

		/**
		* operator+
		*
      * Adds two vectors.
      * @param v - the right hand side of the addition
      * @return TGA::Vector2D - the new Vector2D that is the result
		*/
		Vector2D operator+(Vector2D v);
      
      /**
      * operator-=
      *
      * Subtract a vector to the current vector.
      * @param v - the right hand side
      * @return Vector2D& - reference to the new vector
      */
      Vector2D& operator-=(const Vector2D v);

		/**
		* operator-
		*
		* Subtracts two vectors.
		* @param v - the right hand side of the subtraction
		* @return TGA::Vector2D - the new Vector2D that is the result
		*/
		Vector2D operator-(Vector2D v);

		/**
		* operator*
		*
		* Calculates the scalar product given a scalar.
		* @param scalar - the scalar to multiply by
		* @return TGA::Vector2D - the resultant vector
		*/
		Vector2D operator*(double scalar);

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
		* @param v - the vector to dot with
		* @return double - the dot product
		*/
		double dotProduct(Vector2D v);

		/**
		* length
		*
		* Returns the length of the vector.
		* @return double - the length
		*/
		double length();

		/**
		* distanceFrom
		*
		* Gets the distance from the given "point" to another "point".
		* @param v - the point to calculate distance from
		* @return double - the distance
		*/
		double distanceFrom(Vector2D v);

		/**
		* getX
		*
		* Gets the X component of the vector.
		* @return double - the X component
		*/
		double getX();

		/**
		* getY
		*
		* Gets the Y component of the vector.
		* @return double - the Y component
		*/
		double getY();

      /**
      * setX
      *
      * Set the x component of the vector.
      * @param x - the new x component
      */
      void setX(double x);

      /**
      * setY
      *
      * Set the y component of the vector.
      * @param y - the new y component
      */
      void setY(double y);

	private:
      friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
		double x, y;
	};
}
