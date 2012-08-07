#include "Projectile.h"

Projectile::Projectile(std::string textureName, 
   TGA::BoundingBox bounds, TGA::Vector2D pos, TGA::Vector2D vel)
   : TGA::Collidable(bounds)
   , position(pos)
   , velocity(vel)
{
   texture.loadTexture(textureName);
   
   collided = false;
}


Projectile::~Projectile(void)
{
}

bool Projectile::update()
{
   position += velocity;
   return collided;
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
      collided = true;
      std::cout << "Collided\n";
   }

   if (typeid(collidedWith) == typeid(Player))
   {

   }
// TODO: Projectile to enemy collision
   //if (typeid(collidedWith) == typeid(Enemy))
   //{
   //}
}