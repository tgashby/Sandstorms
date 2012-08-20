/**
 * @file AttackManager.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

#include <vector>

#include "Attack.h"

class AttackManager 
{
public:
   AttackManager ();
   void AddAttack (Attack* attack);
   void UpdateAttacks ();
   void DeleteAttack(Attack* attack);
   std::vector<Attack*> getAttacks();
private:
   std::vector<Attack*> attacks;
};

