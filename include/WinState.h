/**
 * @file WinState.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <State.h>
#include <Texture.h>
#include <BoundingBox.h>

class WinState : public TGA::State
{
public:
   WinState(bool& playAgain);
   ~WinState();

   virtual bool update();

   virtual void draw();

private:
   TGA::Texture winTexture;
   TGA::BoundingBox startGameBox, exitGameBox;
   bool& playAgain;
};
