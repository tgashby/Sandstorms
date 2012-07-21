/**
 * @file Timer.h
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
    * @class Timer
    *
    * @brief Wrapper for SDL_Timer things.
    *
    */
   class Timer
   {
   public:
      /**
      * getTicks
      *
      * Get the number of milliseconds since initialization
      * @return Uint32 - the number of milliseconds
      */
      static Uint32 getTicks();
   private:
   };
}