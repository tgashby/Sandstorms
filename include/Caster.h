/**
 * @file Caster.h
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#pragma once
#include "Enemy.h"

class Caster : public Enemy
{
public:
   Caster (int health, TGA::Vector2D position, TGA::Vector2D velocity = TGA::Vector2D(0, 0), TGA::Vector2D acceleration = TGA::Vector2D(0, 1));
   void update (TGA::Vector2D playerPosition);
private:
   void attack(TGA::Vector2D playerPosition);
   bool attacking, casted;
};

