/**
 * @file Animation.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */

#pragma once

#include "ProjIncludes.h"
#include "TextureManager.h"
#include "BoundingBox.h"
 
namespace TGA
{
   /**
    * @class Animation
    *
    * @brief Represents a single animation, a collection of individual frames.
    *
    * Animations come with a large number of methods for manipulating their
    * frames and playing themselves.
    */
	class Animation
	{
		friend class AnimationManager;

	public:
		/**
		* Animation
		*
		* Constructs an empty animation. (No associated image.)
		*/
		Animation();
		
      /**
      * Animation
      *
      * Constructs an Animation with the given Texture (image).
      * @param texture - a pointer to an image containing the frames.
      */
      Animation(Texture* texture);

      /**
      * ~Animation
      *
      * Unused destructor. All deallocation is handled by the AnimationManager.
      */
      ~Animation();

		
		/**
		* update
		*
		* Makes sure the animation is progressing appropriately.
      * - Checks to make sure the animation isn't playing more times than desired
      * - Updates the current frame if needed
		*/
		void update();

		/**
		* pause
		*
		* Pauses the current animation stopping it from being updated.
		*/
		void pause();

		/**
		* resume
		*
		* Resumes a paused animation, allowing it to once again be updated.
		*/
		void resume();

		/**
		* reset
		*
		* Sets the current frame back to the beginning frame and resumes the animation.
      * @warning Does not reset the number of times the animation will play. 
      * If it is set to play 3 times and it's already played 2, it will only play once more.
		*/
		void reset();

		/**
		* isDone
		*
		* Determines whether or not the animation has played its set number of times.
		* @return bool - true if the animation will not play any more, false if the animation
      * is still playing, or would still play if resumed.
		*/
		bool isDone();

		/**
		* isPaused
		*
		* Determines whether or not the animation is paused.
		* @return bool - true is the animation is paused, false if it isn't.
		*/
		bool isPaused();

		/**
		* deleteMe
		*
		* Tells the AnimationManager to no longer handle this animation.
      * Takes care of all deallocation and removing it from the AnimationManager
		*/
		void deleteMe();

		/**
		* addFrame
		*
		* Adds a frame to the animation given the dimensions and amount of time 
      * it should play.
		* @param frameRect - A rectangle encompassing the frame in the image.
		* @param delay - The amount of time the frame should be shown for.
		*/
		void addFrame(BoundingBox frameRect, Uint32 delay);
      
		/**
		* deleteFrame
		*
		* Removes the frame at the given index from the animation.
		* @param frameNum - the index (0-based) of the frame to remove.
		*/
		void deleteFrame(GLuint frameNum);
      
		/**
		* clearFrames
		*
		* Removes all frames from the animation, leaving it empty.
		*/
		void clearFrames();

		/**
		* goToFrame
		*
		* Sets the currently visible frame to the one specified by the
      * given index.
		* @param frame - the index (0-based) of the frame to show.
		*/
		void goToFrame(GLuint frame);
      
		/**
		* setRepetitions
		*
		* Sets the number of times the animation should play. If the animation
      * had already finished, it starts the animation over again.
		* @param repetitions - the number of times to play the animation. -1 for indefinitely
		*/
		void setRepetitions(int repetitions);
      
		/**
		* setTexture
		*
		* Sets the image to use as the basis for the animation. Especially important if
      * the Animation was created with the empty constructor.
		* @param texture - the pointer to a Texture to use as the image
		*/
		void setTexture(Texture* texture);
      
		/**
		* setDelay
		*
		* Sets the amount of time a frame is shown.
		* @param frame - the index (0-based) of the frame to change.
		* @param delay - the new amount of time to show the frame.
		*/
		void setDelay(GLuint frame, Uint32 delay);
      
		/**
		* setFrameBounds
		*
		* Sets the position and dimensions of a frame on the image.
		* @param frame - the index (0-based) of the frame to change.
		* @param newBounds - the new dimensions of the frame.
		*/
		void setFrameBounds(GLuint frame, BoundingBox newBounds);

		/**
		* draw
		*
		* Draws the current frame at the specified position.
		* @param xPos - the x position of the point at which to draw.
      * @param yPos - the y position of the point at which to draw.
      * @param scaleX - a scale factor in X
      * @param scaleY - a scale factor in Y
      * @param rotation - a rotation, in degrees
		*/
      void draw(GLfloat xPos, GLfloat yPos, float scaleX = 1, float scaleY = 1, float rotation = 0);

		/**
		* getFrameCount
		*
		* Gets the total number of frames for the Animation.
		* @return GLuint - the number of frames in the Animation.
		*/
		GLuint getFrameCount();
      
      /**
       * getCurrentFrameDimensions()
       *
       * Gets the current frame's dimensions
       * @return BoundingBox - the rectangle determining it's position and dimensions
       */
      BoundingBox getCurrentFrameDimensions();

		/**
		* printFrames
		*
		* Creates a pretty representation of each frame with the
      * important information for that frame.
      * Format of a single entry:
      * Frame: #
      * X: # Y: #
      * Width: # Height: #
      * Delay: #
      *
		* @return std::string - the series of entries, one for each frame, in the format
      * listed above
		*/
		std::string printFrames();

	private:
		// The texture panel that has all the frames
		Texture* texture;

		// The individual frames, with delays
		std::vector<std::pair<BoundingBox, Uint32> > frames;

		GLuint currFrame;

		// The last time this animation was updated
		Uint32 lastUpdate;

		bool paused;
		bool done;
		int repetitions;
	};
}