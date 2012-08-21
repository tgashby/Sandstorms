/**
 * @file Enemy.h
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
   Enemy (int health, TGA::Vector2D position, TGA::Vector2D velocity = TGA::Vector2D(0, 0), TGA::Vector2D acceleration = TGA::Vector2D(0, 1));
   virtual void draw();
   virtual void update (TGA::Vector2D playerPosition);
   virtual void handleCollision(TGA::Collidable& collidedWith);
protected:
   void setLeftBound(double newX, double newY);
   void setRightBound(double newX, double newY);
   
   int maxHealth;
   TGA::Vector2D leftBound, rightBound;
};

