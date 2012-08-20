/**
 * @file ProjectileFactory.h
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#ifndef _PROJECTILE_FACTORY_
#define _PROJECTILE_FACTORY_

#include <vector>
#include <algorithm>
#include "Projectile.h"
//class Projectile;

class ProjectileFactory
{
public:
   void addProjectile(Projectile* p);
   void removeProjectile(Projectile* p);
   void update();
   void draw();
   
   std::vector<Projectile*> getProjectiles();
   
private:
   std::vector<Projectile*> projectiles;
};

#endif

