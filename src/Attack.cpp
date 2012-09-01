/**
 * @file Attack.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#include "Attack.h"
#include <Singleton.h>
#include "AttackManager.h"
#include "Caster.h"
#include "Warrior.h"
#include "Hound.h"
#include "Player.h"
#include "Character.h"

Attack::Attack(int damage, TGA::BoundingBox area, Uint32 duration, TGA::Collidable* originator)
: TGA::Collidable(area), originator(originator)
{
   this->damage = damage;
   this->duration = duration;
   TGA::Singleton<AttackManager>::GetSingletonPtr()->AddAttack(this);
}

bool Attack::update()
{
   if (duration == 0)
   {
      return true;
   }
   
   duration--;
   return false;
}

void Attack::handleCollision(TGA::Collidable& collidedWith)
{
   if (originator != &collidedWith)
   {
      if (typeid(collidedWith) == typeid(Player)
          || typeid(collidedWith) == typeid(Caster)
          || typeid(collidedWith) == typeid(Warrior)
          || typeid(collidedWith) == typeid(Hound))
      {
         ((Character&)collidedWith).takeDamage(damage);
         
         // Make sure this attack is only used once.
         TGA::Singleton<AttackManager>::GetSingletonPtr()->DeleteAttack(this);
      }
   }
}
