/**
 * @file Texture.h
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
      * @param std::string fileName - the path to the file, relative path is acceptable
		*/
		Texture(std::string fileName);

		~Texture();

		/**
		* loadTexture
		*
		* Loads a texture from a file specified.
		* @param std::string imgFileName - the path to the file, relative path is acceptable
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
      * @param GLfloat xPos - the x position at which to start drawing
      * @param GLfloat yPos - the y position at which to start drawing
		*/
		void draw(GLfloat xPos, GLfloat yPos);

		/**
		* drawSection
		*
      * Draws a small portion of a texture, useful, for example, in a
      * sprite sheet.
		* @param GLfloat xPos - the x position at which to start drawing
		* @param GLfloat yPos - the y position at which to start drawing
		* @param SDL_Rect section - a rectangle representation of the section to draw
		*/
		void drawSection(GLfloat xPos, GLfloat yPos, SDL_Rect section);

		/**
		* drawSection
		*
		* Draws a small portion of a texture, useful, for example, in a
      * sprite sheet.
      * @param GLfloat xPos - the x position at which to start drawing
      * @param GLfloat yPos - the y position at which to start drawing 
		* @param int sectX - the x position on the texture to start the section
		* @param int sectY - the y position on the texture to start the section
		* @param int sectWidth - the width of the section
		* @param int sectHeight - the height of the section
		*/
		void drawSection(GLfloat xPos, GLfloat yPos, int sectX, int sectY,
			int sectWidth, int sectHeight);

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