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
   maxHealth = health;
}

void Enemy::draw()
{
   float redTint, greenTint, blueTint;
   
   if (health / maxHealth == 1)
   {
      redTint = greenTint = blueTint = 1.0f;
   }
   else if (static_cast<float>(health) / maxHealth > 0.75)
   {
      redTint = 1.0f;
      greenTint = 0.4f;
      blueTint = 0.4f;
   }
   else if (static_cast<float>(health) / maxHealth > 0.5)
   {
      redTint = 1.0f;
      greenTint = 0.2f;
      blueTint = 0.2f;
   }
   else
   {
      redTint = 1.0f;
      greenTint = 0.0f;
      blueTint = 0.0f;
   }
   
   Character::draw(0, 1, 1, 0, redTint, greenTint, blueTint);
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