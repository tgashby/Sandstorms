/**
 * @file Enemy.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#include "Enemy.h"

Enemy::Enemy( int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/ )
{

}

void Enemy::handleCollision( TGA::Collidable& collidedWith )
{
   throw std::exception("The method or operation is not implemented.");
}

