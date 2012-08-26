#include "Projectile.h"
#include "Player.h"
#include "Platform.h"
#include "ProjectileFactory.h"
#include "Caster.h"
#include "Warrior.h"
#include "Hound.h"

Projectile::Projectile(int damage, std::string textureName,
                       TGA::BoundingBox bounds, TGA::Vector2D pos, TGA::Vector2D vel)
   : TGA::Collidable(bounds)
   , position(pos)
   , velocity(vel)
   , damage(damage)
{
   texture.loadTexture(textureName);
}


Projectile::~Projectile(void)
{
}

void Projectile::update()
{
   position += velocity;
   
   bounds.setX(position.getX());
   bounds.setY(position.getY());
}

void Projectile::draw()
{
   float scaleX = velocity.getX() < 0 ? -1.0f : 1.0f;
   
   texture.draw(static_cast<float>(position.getX()), static_cast<float>(position.getY()),
                scaleX);
}

void Projectile::handleCollision( Collidable& collidedWith )
{
   if (typeid(collidedWith) == typeid(Platform))
   {
      TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->removeProjectile(this);
   }
   
   if (typeid(collidedWith) == typeid(Caster)
       || typeid(collidedWith) == typeid(Warrior)
       || typeid(collidedWith) == typeid(Hound))
   {
      ((Character&)collidedWith).takeDamage(damage);
      TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->removeProjectile(this);
   }
   
   if (typeid(collidedWith) == typeid(Player))
   {
      ((Player&)collidedWith).takeDamage(damage);
      TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->removeProjectile(this);
   }
}