/**
 * @file StateManager.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once
#include <vector>

class State;

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

