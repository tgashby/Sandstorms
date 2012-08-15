#include "Character.h"

Character::Character( int health /*= 100*/, TGA::Vector2D position /*= TGA::Vector2D(0,0)*/, 
   TGA::Vector2D velocity /*= TGA::Vector2D(0,0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 0.05)*/)
   : Collidable(TGA::BoundingBox(0,0,0,0))
   , position(position)
   , velocity(velocity)
   , acceleration(acceleration)
{
   this->health = health;
   alive = true;

   currAnimation = NULL;
}

Character::~Character()
{
   // TODO: Memory management?
}

void Character::update()
{
   velocity += acceleration;

   position += velocity;

   assert(currAnimation);
   currAnimation->update();
}

void Character::draw( float interpolation, float scaleX /*= 1*/, float scaleY /*= 1*/, float rotation /*= 0*/ )
{
   // TODO: Handle interpolation

   if (facingLeft)
   {
      scaleX = -1;
   }

   assert(currAnimation);
   currAnimation->draw(static_cast<float>(position.getX()), static_cast<float>(position.getY()),
      scaleX, scaleY, rotation);
}

TGA::Vector2D Character::getPosition()
{
   return position;
}

bool Character::isAlive()
{
   return alive;
}
