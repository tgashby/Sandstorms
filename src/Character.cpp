#include "Character.h"
#include <Collision.h>

Character::Character( int health /*= 100*/, TGA::Vector2D position /*= TGA::Vector2D(0,0)*/, TGA::Vector2D velocity /*= TGA::Vector2D(0,0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/)
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
   
   if (health <= 0)
   {
      alive = false;
   }
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

void Character::takeDamage(int amount)
{
   health -= amount;
}

void Character::collideWithPlatform(Platform& collidedWith)
{
   bool onlyHeadColliding = collidedWithOnlySubBound(0, collidedWith);
   bool onlyLeftColliding = collidedWithOnlySubBound(1, collidedWith);
   bool onlyRightColliding = collidedWithOnlySubBound(2, collidedWith);
   bool onlyFeetColliding = collidedWithOnlySubBound(3, collidedWith);
   
   currAnimation->resume();
   
   // If only head is colliding, below platform
   if (onlyHeadColliding)
   {
      velocity.setY(0);
      position.setY(collidedWith.getBounds().getY()
                    + collidedWith.getBounds().getHeight());
   }
   // Left side of torso is colliding, on right side of platform
   else if (onlyLeftColliding)
   {
      position.setX(collidedWith.getBounds().getX()
                    + collidedWith.getBounds().getWidth());
   }
   // Right side of torso colliding, on left side of platform
   else if (onlyRightColliding)
   {
      position.setX(collidedWith.getBounds().getX()
                    - currAnimation->getCurrentFrameDimensions().getWidth());
   }
   // Feet colliding, above platform
   else if (onlyFeetColliding)
   {
      velocity.setY(0);
      position.setY(collidedWith.getBounds().getY()
                    - currAnimation->getCurrentFrameDimensions().getHeight() + 1);
   }
   else // More than one sub-boundary
   {
      TGA::BoundingBox leftSide(static_cast<int>(position.getX()), static_cast<int>(position.getY()),
                                currAnimation->getCurrentFrameDimensions().getWidth() / 2,
                                currAnimation->getCurrentFrameDimensions().getHeight());
      
      TGA::BoundingBox rightSide(static_cast<int>(position.getX()) +
                                 currAnimation->getCurrentFrameDimensions().getWidth() / 2,
                                 static_cast<int>(position.getY()),
                                 currAnimation->getCurrentFrameDimensions().getWidth() / 2,
                                 currAnimation->getCurrentFrameDimensions().getHeight());
      
      if (TGA::Collision::checkCollision(leftSide, collidedWith.getBounds()))
      {
         position.setX(collidedWith.getBounds().getX()
                       + collidedWith.getBounds().getWidth());
      }
      
      if (TGA::Collision::checkCollision(rightSide, collidedWith.getBounds()))
      {
         position.setX(collidedWith.getBounds().getX()
                       - currAnimation->getCurrentFrameDimensions().getWidth());
      }
   }
}

void Character::makeSubBounds()
{
   int frameHeight = currAnimation->getCurrentFrameDimensions().getHeight();
   int frameWidth = currAnimation->getCurrentFrameDimensions().getWidth();
   
   bounds = TGA::BoundingBox((int)position.getX(), (int)position.getY(), frameWidth, frameHeight);
   
   // "Head" box, top 20%
   subBounds[0] = TGA::BoundingBox((int)position.getX(), (int)position.getY(), frameWidth, frameHeight / 5 + 1);
   
   // "Left torso" box, middle 60% left side
   subBounds[1] = TGA::BoundingBox((int)position.getX(), (int)position.getY() + frameHeight / 5 + 1, frameWidth / 2 + 1,
                                   (int)(frameHeight * 0.6) + 1);
   
   // "Right torso" box
   subBounds[2] = TGA::BoundingBox((int)position.getX() + frameWidth / 2 + 1, (int)position.getY() + frameHeight / 5 + 1,
                                   frameWidth / 2 + 1, (int)(frameHeight * 0.6) + 1);
   
   // "Legs" box
   if (facingLeft)
   {
      subBounds[3] = TGA::BoundingBox((int)position.getX(), (int)position.getY() + (int)(frameHeight * 0.8) + 1, frameWidth - 46, frameHeight / 5 + 1);
   }
   else
   {
      subBounds[3] = TGA::BoundingBox((int)position.getX() + 46, (int)position.getY() + (int)(frameHeight * 0.8) + 1, frameWidth, frameHeight / 5 + 1);
   }
}

bool Character::collidedWithOnlySubBound(int ndx, TGA::Collidable& collidedWith)
{
   bool onlyNdx = (TGA::Collision::checkCollision(subBounds[ndx], collidedWith.getBounds())
                   && !TGA::Collision::checkCollision(subBounds[(ndx + 1) % 4], collidedWith.getBounds())
                   && !TGA::Collision::checkCollision(subBounds[(ndx + 2) % 4], collidedWith.getBounds())
                   && !TGA::Collision::checkCollision(subBounds[(ndx + 3) % 4], collidedWith.getBounds()));
   
   return onlyNdx;
}