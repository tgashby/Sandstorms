/**
 * @file LevelState.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <State.h>
#include "Level.h"

class LevelState : public TGA::State {
public:
  LevelState (Level level);
  bool update ();
  void draw ();
private:
   Level level;
};

