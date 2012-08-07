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
   std::vector<int> removeNdxs;

   if (projectiles.size() > 0)
   {
      for (std::vector<Projectile*>::size_type i = 0; i < projectiles.size(); i++)
      {
         if (projectiles.at(i)->update())
         {
            removeNdxs.push_back(i);
         }
      }
   }

   for (std::vector<int>::iterator i = removeNdxs.begin(); i < removeNdxs.end(); i++)
   {
      removeProjectile(projectiles.at(*i));
   }
}

void ProjectileFactory::draw()
{
   if (projectiles.size() > 0)
   {
      for (projItr i = projectiles.begin(); i < projectiles.end(); i++)
      {
         (*i)->draw();
      }
   }
}

std::vector<Projectile*> ProjectileFactory::getProjectiles()
{
   return projectiles;
}
