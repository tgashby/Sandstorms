/**
 * @file EnergyPickup.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once
#include "Consumable.h"

class ManaPickup : public Consumable 
{
public:
   ManaPickup (int potency, TGA::Vector2D position);
   void handleCollision( TGA::Collidable& collidedWith );
protected:
   int potency;
};

