//
//  StoryState.cpp
//  Sandstorms
//
//  Created by Taggart Ashby on 8/28/12.
//
//

#include "StoryState.h"
#include <Timer.h>
#include <Engine.h>

StoryState::StoryState(std::string textureName, Uint32 howLong)
{
   storyTexture.loadTexture(textureName);
   this->howLong = howLong * 1000;
   lastUpdate = -1;
}

bool StoryState::update()
{
   if (lastUpdate == -1)
   {
      lastUpdate = TGA::Timer::getTicks();
   }
   
   if (TGA::Timer::getTicks() - lastUpdate > howLong)
   {
      return false;
   }
   
   return true;
}

void StoryState::draw()
{
   storyTexture.draw(0, 0);
   TGA::Singleton<TGA::Engine>::GetSingletonPtr()->Graphics->swapBuffers();
}