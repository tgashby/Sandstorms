/**
 * @file MenuState.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

class MenuState 
{
public:
  MenuState ();
  bool update ();
  void draw ();
private:
   TGA::Texture menuTexture;
};

