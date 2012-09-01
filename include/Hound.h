/**
 * @file Hound.h
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#pragma once
#include "Enemy.h"

class Hound : public Enemy
{
public:
   Hound (int health, TGA::Vector2D position, TGA::Vector2D velocity = TGA::Vector2D(0, 0), TGA::Vector2D acceleration = TGA::Vector2D(0, 1));
   ~Hound();
   void update (TGA::Vector2D playerPosition);
   
private:
   bool barking;
};

