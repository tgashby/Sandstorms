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
   , leftBound(0,0)
   , rightBound(0,0)
{
   
}

void Enemy::update(TGA::Vector2D playerPosition)
{
   makeSubBounds();
   Character::update();
}

void Enemy::handleCollision(TGA::Collidable& collidedWith)
{
   if (typeid(collidedWith) == typeid(Platform))
   {
      collideWithPlatform((Platform&)collidedWith);
      
      if (collidedWithOnlySubBound(1, collidedWith) || collidedWithOnlySubBound(2, collidedWith))
      {
         velocity.setX(-velocity.getX());
      }
   }
}

void Enemy::setLeftBound(double newX, double newY)
{
   leftBound = TGA::Vector2D(newX, newY);
}

void Enemy::setRightBound(double newX, double newY)
{
   rightBound = TGA::Vector2D(newX, newY);
}