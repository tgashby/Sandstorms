/**
 * @file StateManager.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once
#include <vector>

#include "State.h"

namespace TGA
{
   /**
    * @class StateManager
    *
    * @brief Manages all the states of the game
    *
    * Simply calling UpdateCurrentState will handle moving between states.
    */
   class StateManager
   {
   public:
      void PushState (State* state);
      void UpdateCurrentState ();
      void DrawCurrentState ();
   private:
      void PopState ();
      std::vector<State*> states;
   };
}
