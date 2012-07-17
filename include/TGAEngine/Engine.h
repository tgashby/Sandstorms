/**
 * @file Engine.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#pragma once

#include "Singleton.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "InputManager.h"

namespace TGA
{
   /**
    * @class Engine
    *
    * @brief The big Engine class containing all the Managers and other classes.
    *
    * Engine holds all the Manager classes and other useful ones, like Camera.
    */
	class Engine
	{
	public:
		/**
		* Engine
		* 
      * Creates and initializes all Managers and other classes in Engine.
		*/
		Engine();

		/**
		* ~Engine
		*
      * Deallocates all Managers and classes.
		*/
		~Engine();


		AnimationManager* Animations;
		TextureManager* Textures;
		Camera* GameCamera;
		GraphicsManager* Graphics;
		InputManager* Input;

   private:
      void initalize();
      void shutdown();
	};
}

