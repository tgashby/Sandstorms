/**
 * @file Warrior.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once
#include "Enemy.h"

class Warrior : public Enemy 
{
public:
  Warrior (int health, TGA::Vector2D position, TGA::Vector2D velocity = TGA::Vector2D(0, 0), TGA::Vector2D acceleration = TGA::Vector2D(0, 1));
  void update ();
};

