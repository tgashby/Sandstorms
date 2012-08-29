/**
 * @file MenuState.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <Texture.h>
#include <BoundingBox.h>
#include <State.h>

class MenuState : public TGA::State
{
public:
   MenuState ();
   bool update ();
   void draw ();
private:
   TGA::Texture menuTexture;
   TGA::BoundingBox startGameBox, exitGameBox;
};