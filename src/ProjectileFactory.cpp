#include "ProjectileFactory.h"

typedef std::vector<Projectile*>::iterator projItr;

void ProjectileFactory::addProjectile( Projectile* p )
{
   projectiles.push_back(p);
}

void ProjectileFactory::removeProjectile( Projectile* p )
{
   projItr pos = find(projectiles.begin(), projectiles.end(), p);
   
   if (pos != projectiles.end())
   {
      projectiles.erase(pos);
   }
}

void ProjectileFactory::update()
{
   for (std::vector<Projectile*>::size_type i = 0; i < projectiles.size(); i++)
   {
      projectiles.at(i)->update();
   }
}

void ProjectileFactory::draw()
{
   for (projItr i = projectiles.begin(); i < projectiles.end(); i++)
   {
      (*i)->draw();
   }
}

std::vector<Projectile*> ProjectileFactory::getProjectiles()
{
   return projectiles;
}
