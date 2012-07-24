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

void Character::update(Uint32 dt)
{
   velocity += acceleration * dt;

   //if (velocity.length() != 0.0)
   //{
   //   std::cout << "Position: " << position;
   //   std::cout << "Velocity: " << velocity;
   //   std::cout << "Acceleration: " << acceleration;
   //   std::cout << "dt: " << dt << "\n";
   //}

   position += velocity * dt;

   assert(currAnimation);
   currAnimation->update();
}

void Character::draw(bool flipped /* = false */)
{
   assert(currAnimation);
   currAnimation->draw(static_cast<float>(position.getX()), static_cast<float>(position.getY()),
      flipped);
}

TGA::Vector2D Character::getPosition()
{
   return position;
}

bool Character::isAlive()
{
   return alive;
}
