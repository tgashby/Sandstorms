/**
 * @file LoseState.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */

#pragma once

#include <State.h>
#include <Texture.h>
#include <BoundingBox.h>

class LoseState : public TGA::State
{
public:
   LoseState(bool& playAgain);
   ~LoseState();

   virtual bool update();

   virtual void draw();

private:
   TGA::Texture loseTexture;
   TGA::BoundingBox startGameBox, exitGameBox;
   bool& playAgain;
};
