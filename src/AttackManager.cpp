/**
 * @file AttackManager.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#include "AttackManager.h"
#include "Attack.h"

AttackManager::AttackManager()
{
   
}

void AttackManager::AddAttack( Attack* attack )
{
   attacks.push_back(attack);
}

void AttackManager::UpdateAttacks()
{
   for (std::vector<Attack*>::iterator i = attacks.begin(); i < attacks.end(); i++)
   {
      (*i)->update();
   }
}

void AttackManager::DeleteAttack(Attack *attack)
{
   std::vector<Attack*>::iterator pos = find(attacks.begin(), attacks.end(), attack);
   
   if (pos != attacks.end())
   {
      attacks.erase(pos);
   }
}

std::vector<Attack*> AttackManager::getAttacks()
{
   return attacks;
}