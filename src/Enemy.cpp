/**
 * @file Enemy.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#include "Enemy.h"
#include "Platform.h"

Enemy::Enemy( int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/ )
   : Character(health, position, velocity, acceleration)
{
   
}

void Enemy::update()
{
   makeSubBounds();
   Character::update();
}

void Enemy::handleCollision(TGA::Collidable& collidedWith)
{
   if (typeid(collidedWith) == typeid(Platform))
   {
      collideWithPlatform((Platform&)collidedWith);
   }
}
