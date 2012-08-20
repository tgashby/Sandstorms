/**
 * @file HealthPickup.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#include "HealthPickup.h"
#include "Player.h"

HealthPickup::HealthPickup( int potency, TGA::Vector2D position )
   : Consumable("resources/pickups/health_pickup.png", position)
{
   this->potency = potency;
}

void HealthPickup::handleCollision( TGA::Collidable& collidedWith )
{
   if (typeid(collidedWith) == typeid(Player))
   {
      if (!used)
      {
         ((Player&)collidedWith).addHealth(potency);
      }
      
      used = true;
   }
}
