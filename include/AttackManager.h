/**
 * @file AttackManager.h
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#pragma once

class Attack;

class AttackManager 
{
public:
   AttackManager ();
   void RegisterAttack (Attack* attack);
   void UpdateAttacks ();
private:
   std::vector<Attack*> attacks;
};

