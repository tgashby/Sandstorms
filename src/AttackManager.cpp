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
   std::vector<std::vector<Attack*>::size_type> removeNdxs;

   for (std::vector<Attack*>::size_type i = 0; i < attacks.size(); i++)
   {
      if (attacks.at(i)->update())
      {
         removeNdxs.push_back(i);
      }
   }

   for (std::vector<std::vector<Attack*>::size_type>::size_type i = 0; i < removeNdxs.size(); i++)
   {
      attacks.erase(attacks.begin() + removeNdxs.at(i));
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