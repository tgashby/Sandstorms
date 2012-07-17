/**
 * @file GraphicsManager.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once
#include "ProjIncludes.h"
#include "TextureManager.h"

namespace TGA
{
   /**
    * @class GraphicsManager
    *
    * @brief Handles the window.
    *
    * GraphicsManager handles creating and manipulating the game window.
    */
	class GraphicsManager
	{
	public:
		/**
		* GraphicsManager
		*
		* Creates a GraphicsManager.
      * @warning GraphicsManager.init(...) MUST be called before GraphicsManager will
      * be useful.
		*/
		GraphicsManager();

		/**
		* ~GraphicsManager
		*
		* Handles deallocating and destroying the window and its components.
		*/
		~GraphicsManager();

		/**
		* init
		*
		* Initializes the window to a specific size, title, and position.
      * All parameters are optional.
      * Default values are: 1024x512, no title, and the window centered in the screen.
		* @param int screenWidth - the window width
		* @param int screenHeight - the window height
		* @param std::string winTitle - the title of the window (what appears in its upper-left corner)
		* @param int screenX - the x position of the window on the screen
		* @param int screenY - the y position of the window on the screen
		*/
		void init(int screenWidth = 1024, int screenHeight = 512, 
		 std::string winTitle = "", int screenX = SDL_WINDOWPOS_CENTERED, int screenY = SDL_WINDOWPOS_CENTERED);

		/**
		* shutDown
		*
		* Deallocates and destroys the window. (Called automatically by destructor)
		*/
		void shutDown();

		/**
		* swapBuffers
		*
		* Swaps the screen buffers. This should be called after every draw cycle in the game.
		*/
		void swapBuffers();

		/**
		* resizeWindow
		*
		* Resizes the window to new dimensions.
		* @param int screenWidth - the new width
		* @param int screenHeight - the new height
		*/
		void resizeWindow(int screenWidth, int screenHeight);
		
      /**
      * toggleFullScreen
      *
      * Switches the window between full screen and windowed.
      */
      void toggleFullScreen();

	private:
		void initGL();

		int screenWidth;
		int screenHeight;

		bool isLoaded;
		SDL_bool isFullScreen;

		std::string winTitle;
		SDL_Window* window;
		SDL_GLContext glCtx;
	};
}


