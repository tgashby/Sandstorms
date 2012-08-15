/**
 * @file EnergyPickup.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#include "ManaPickup.h"
#include "Player.h"

ManaPickup::ManaPickup( int potency, TGA::Vector2D position )
   : Consumable("../resources/pickups/mana_pickup.png", position)
{
   this->potency = potency;
}

void ManaPickup::handleCollision( TGA::Collidable& collidedWith )
{
   if (typeid(collidedWith) == typeid(Player))
   {
      if (!used)
      {
         ((Player&)collidedWith).addMana(potency);
      }

      used = true;
   }
}
