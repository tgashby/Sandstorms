/**
 * @file HealthPickup.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once
#include "Consumable.h"

class HealthPickup : public Consumable 
{
public:
   HealthPickup (int potency, TGA::Vector2D position);
   void handleCollision(TGA::Collidable& collidedWith);
private:
   int potency;
};

