/**
 * @file AnimationManager.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#pragma once

#include "ProjIncludes.h"
#include "Animation.h"

namespace TGA
{
   /**
    * @class AnimationManager
    *
    * @brief Manages all Animations. Animations are automatically added
    * to the manager upon creation.
    *
    * AnimationManager is one of the Singleton Managers
    */
	class AnimationManager
	{
		friend class Animation;

	public:
		/**
		* AnimationManager
		*
		* Constructor, clears animations.
		*/
		AnimationManager();
		
      /**
      * ~AnimationManager
      *
      * Removes all animations and deallocates them.
      * Calls removeAll()
      */
      ~AnimationManager();

		
		/**
		* removeAll
		*
		* Removes every animation from the list and deallocates them.
		*/
		void removeAll();
						
		/**
		* pauseAll
		*
		* Pauses (Animation.pause()) every animation in the list.
		*/
		void pauseAll();

		/**
		* resumeAll
		*
		* Resumes (Animation.resume()) every animation in the list.
		*/
		void resumeAll();
		
		/**
		* updateAll
		*
		* Updates (Animation.update()) all animations in the list.
		*/
		void updateAll();

		/**
		* resetAll
		*
		* Resets (Animation.reset()) all animations in the list
		*/
		void resetAll();

	protected:
		// Add animation to be managed
		void addAnimation(Animation* animation);

		// Remove an animation from being managed
		void removeAnimation(Animation* animation);

		// The animations and their IDs
		std::vector<Animation*> animations;
	};
}