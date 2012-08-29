//
//  StoryState.h
//  Sandstorms
//
//  Created by Taggart Ashby on 8/28/12.
//
//

#ifndef __Sandstorms__StoryState__
#define __Sandstorms__StoryState__

#include <iostream>
#include <Texture.h>
#include <BoundingBox.h>
#include <State.h>

class StoryState : public TGA::State
{
public:
   StoryState (std::string textureName, Uint32 howLong);
   bool update ();
   void draw ();
private:
   TGA::Texture storyTexture;
   Uint32 howLong, lastUpdate;
};

#endif /* defined(__Sandstorms__StoryState__) */
