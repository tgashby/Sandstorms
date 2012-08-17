/**
 * @file State.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

class State 
{
public:
  virtual bool update () = 0;
  virtual void draw () = 0;
};

