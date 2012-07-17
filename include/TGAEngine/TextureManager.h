/**
 * @file TextureManager.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once

#include "ProjIncludes.h"
#include "Texture.h"

namespace TGA
{
   /**
    * @class TextureManager
    *
    * @brief Manages all textures. Textures are automatically added to the manager upon creation.
    *
    * TextureManager is a collection of all textures. It will be a Singleton along with the other managers.
    * TextureManager is used to act on all Textures at once so that the developer need not keep track of them all.
    */
	class TextureManager
	{
		friend class Texture;

	public:
		/**
		* TextureManager
		*
		* Creates a TextureManager and clears out all textures.
		*/
		TextureManager();

		/**
		* ~TextureManager
		*
		* Deallocates and cleans up all textures.
		*/
		~TextureManager();

		/**
		* resetTextures
		*
      * Reset all textures, useful after a screen resize
		*/
		void resetTextures();

		/**
		* removeAllTextures
		*
		* Deallocates and cleans up all textures. Called by destructor.
		*/
		void removeAllTextures();

	protected:
		// Add a texture to be managed
		void addTexture(Texture* texture);
		// Remove a texture from being managed
		void removeTexture(Texture* texture);

		// The stored textures
		std::vector<Texture*> textures;
	};
}