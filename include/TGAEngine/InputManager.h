/**
 * @file InputManager.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once

#include "Key.h"

namespace TGA
{
   /**
    * @class InputManager
    *
    * @brief Manages the keyboard and mouse.
    *
    * InputManager is one of the Manager classes. It keeps
    * track of the keyboard and mouse state.
    */
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		
		/**
		* keyDown
		*
		* Determines if the given key is currently depressed.
		* @param Key key - the key being polled
		* @return bool - true if the key is depressed
		*/
		bool keyDown(Key key);

		/**
		* update
		*
		* Keeps the key states and mouse position in sync with reality.
		* @return bool - returns false if a SDL_QUIT event was triggered.
      * Don't like this... but for now it's there.
		*/
		bool update();

		/**
		* getMouseCoords
		*
		* Gets the current position of the mouse.
		* @return SDL_Point - a point representation of the mouse coordinates
		*/
		SDL_Point getMouseCoords();

	private:
		std::map<int, bool> keystates;
		int mouseX;
		int mouseY;
	};
}