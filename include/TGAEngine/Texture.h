/**
 * @file Texture.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */
#pragma once

#include "ProjIncludes.h"
#include "Singleton.h"
#include "Camera.h"

namespace TGA
{
	/**
	 * @class Texture
	 *
	 * @brief Represents a texture (image)
	 *
	 * Texture is used to store all images in the game, regardless of
    * if their use is actually a texture or not...
	 */
	class Texture
	{
		friend class TextureManager;

	public:
		/**
		* Texture
		*
		* Creates an empty texture to be loaded into later.
		*/
		Texture();

		/**
		* Texture
		*
      * Creates a texture from the file given.
      * @param fileName - the path to the file, relative path is acceptable
		*/
		Texture(std::string fileName);

		~Texture();

		/**
		* loadTexture
		*
		* Loads a texture from a file specified.
		* @param imgFileName - the path to the file, relative path is acceptable
		* @return bool - true if loading succeeds
		*/
		bool loadTexture(std::string imgFileName);

      /**
      * reset
      *
      * Resets the texture, reloading it from disk. Often needed after a
      * screen size change.
      * @return bool - true if loading succeeds
      */
      bool reset();

		/**
		* deleteMe
		*
		* Tells the TextureManager that this texture is ready to be freed.
		*/
		void deleteMe();

		/**
		* draw
		*
		* Draws the entire texture at a location.
      * @param xPos - the x position at which to start drawing
      * @param yPos - the y position at which to start drawing
      * @param scaleX - a scale factor in X
      * @param scaleY - a scale factor in Y
      * @param rotation - a rotation, in degrees
      * @param redTint - the amount of red to overlay
      * @param greenTint - the amount of green to overlay
      * @param blueTint - the amount of blue to overlay
		*/
		void draw(float xPos, float yPos, float scaleX = 1, float scaleY = 1, float rotation = 0, float redTint = 1.0, float greenTint = 1.0, float blueTint = 1.0);

		/**
		* drawSection
		*
      * Draws a small portion of a texture, useful, for example, in a
      * sprite sheet.
		* @param xPos - the x position at which to start drawing
		* @param yPos - the y position at which to start drawing
      * @param section - a rectangle representation of the section to draw
      * @param scaleX - a scale factor in X
      * @param scaleY - a scale factor in Y
      * @param rotation - a rotation, in degrees
      * @param redTint - the amount of red to overlay
      * @param greenTint - the amount of green to overlay
      * @param blueTint - the amount of blue to overlay
		*/
      void drawSection(float xPos, float yPos, SDL_Rect section, float scaleX = 1, float scaleY = 1, float rotation = 0, float redTint = 1.0, float greenTint = 1.0, float blueTint = 1.0);

		/**
		* drawSection
		*
		* Draws a small portion of a texture, useful, for example, in a
      * sprite sheet.
      * @param xPos - the x position at which to start drawing
      * @param yPos - the y position at which to start drawing 
		* @param sectX - the x position on the texture to start the section
		* @param sectY - the y position on the texture to start the section
		* @param sectWidth - the width of the section
      * @param sectHeight - the height of the section
      * @param scaleX - a scale factor in X
      * @param scaleY - a scale factor in Y
      * @param rotation - a rotation, in degrees
      * @param redTint - the amount of red to overlay
      * @param greenTint - the amount of green to overlay
      * @param blueTint - the amount of blue to overlay
		*/
		void drawSection(float xPos, float yPos, int sectX, int sectY,
         int sectWidth, int sectHeight, float scaleX = 1, float scaleY = 1, float rotation = 0, float redTint = 1.0, float greenTint = 1.0, float blueTint = 1.0);

		/**
		* getWidth
		*
		* Gets the width of the image
		* @return GLsizei - the width of the image
		*/
		GLsizei getWidth();

		/**
		* getHeight
		*
		* Gets the height of the image.
		* @return GLsizei - the height of the image
		*/
		GLsizei getHeight();

	private:
		GLuint texture;
		std::string fileName;
		GLsizei width;
		GLsizei height;
	};
}