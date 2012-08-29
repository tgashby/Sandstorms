/**
 * @file State.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

namespace TGA
{
   /**
    * @class State
    *
    * @brief A State is any state of the game, like Menu, Game, Win, Lose, Etc.
    *
    * This class is just an interface for more specific States.
    * States are to be used with the StateManager.
    */
   class State
   {
   public:
      /**
       * update
       *
       * Updates the state.
       * @return bool - whether the state is over or not.
       */
      virtual bool update () = 0;
      
      /**
       * draw
       *
       * Draws the state.
       */
      virtual void draw () = 0;
   };
}