#include "Player.h"

const int PLAYER_MAX_HEALTH = 250;
const int MAX_HORIZ_VEL = 1;
const int MAX_JUMP_LENGTH = 10000;

typedef std::pair<std::string, TGA::Animation*> animPair;

Player::Player( TGA::Vector2D position /*= TGA::Vector2D(0,0)*/ )
   : Character(PLAYER_MAX_HEALTH, position)
{
   maxHealth = PLAYER_MAX_HEALTH;
   hasJumped = hasDoubleJumped = false;
   lastJumpTime = 0;

   TGA::Texture* idleTex = new TGA::Texture("../resources/player/idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 138, 202), 1000000);
   idleAnim->setRepetitions(-1);

   // TODO: Finishing adding player animations

   animations.insert(animations.begin(), animPair("idle", idleAnim));

   currAnimation = idleAnim;


   // DEBUG
   acceleration.setY(0);
}

void Player::update(float dt)
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   
   if (!engine->Input->keyDown(TGA::key_A) && 
       !engine->Input->keyDown(TGA::key_D))
   {
      velocity.setX(0);
      acceleration.setX(0);
   }
   else
   {
      if (engine->Input->keyDown(TGA::key_D))
      {
         if (abs(velocity.getX()) < MAX_HORIZ_VEL)
         {
            acceleration.setX(0.5);
         }
         else
         {
            acceleration.setX(0);
         }
      }

      if (engine->Input->keyDown(TGA::key_A))
      {
         if (abs(velocity.getX()) < MAX_HORIZ_VEL)
         {
            acceleration.setX(-0.5);
         }
         else
         {
            acceleration.setX(0);
         }
      }
   }

   if (engine->Input->keyDown(TGA::key_SPACE))
   {
      if (!hasJumped || !hasDoubleJumped)
      {
         jump();
      }
   }

   makeSubBounds();

   Character::update(dt);
}

float Player::getHealthPercent()
{
   return ((float)health / maxHealth);
}

void Player::jump()
{
   if (lastJumpTime == 0)
   {
      lastJumpTime = TGA::Timer::getTicks();
   }

   velocity.setY(velocity.getY() - 3);

   if (TGA::Timer::getTicks() - lastJumpTime < MAX_JUMP_LENGTH)
   {
      if (!hasJumped)
      {
         hasJumped = true;
      }
      else if (!hasDoubleJumped)
      {
         hasDoubleJumped = true;
      }
   }
}

void Player::handleCollision( TGA::Collidable& collidedWith )
{
   if (typeid(collidedWith) == typeid(Platform))
   {
      // If only head is colliding, below platform
      if (collidedWithOnlySubBound(0, collidedWith))
      {
         velocity.setY(0);
         position.setY(collidedWith.getBounds().getY() 
            + collidedWith.getBounds().getHeight());
      }

      // If only left side of torso is colliding, on right side of platform
      if (collidedWithOnlySubBound(1, collidedWith))
      {
         position.setX(collidedWith.getBounds().getX() 
            + collidedWith.getBounds().getWidth());
      }

      // If only right side of torso is colliding, on left side of platform
      if (collidedWithOnlySubBound(2, collidedWith))
      {
         position.setX(collidedWith.getBounds().getX()
            - currAnimation->getCurrentFrameDimensions().getWidth());
      }

      // If only feet are colliding, above platform
      if (collidedWithOnlySubBound(3, collidedWith))
      {
         velocity.setY(0);
         position.setY(collidedWith.getBounds().getY() 
            - currAnimation->getCurrentFrameDimensions().getHeight());

         hasJumped = hasDoubleJumped = false;
      }
   }
   
}

void Player::makeSubBounds()
{
   int frameHeight = currAnimation->getCurrentFrameDimensions().getHeight();
   int frameWidth = currAnimation->getCurrentFrameDimensions().getWidth();

   // "Head" box, top 20%
   subBounds[0] = TGA::BoundingBox(0, 0, frameWidth, frameHeight / 5);

   // "Left torso" box, middle 60% left side
   subBounds[1] = TGA::BoundingBox(0, frameHeight / 5, frameWidth / 2, 
      (int)(frameHeight * 0.6));

   // "Right torso" box
   subBounds[2] = TGA::BoundingBox(frameWidth / 2, frameHeight / 5, 
      frameWidth / 2, (int)(frameHeight * 0.6));

   // "Legs" box
   subBounds[3] = TGA::BoundingBox(0, (int)(frameHeight * 0.8), frameWidth, frameHeight / 5);
}

bool Player::collidedWithOnlySubBound(int ndx, TGA::Collidable& collidedWith)
{
   bool onlyNdx = (TGA::Collision::checkCollision(subBounds[ndx], collidedWith.getBounds()) 
      && !TGA::Collision::checkCollision(subBounds[(ndx + 1) % 4], collidedWith.getBounds()) 
      && !TGA::Collision::checkCollision(subBounds[(ndx + 2) % 4], collidedWith.getBounds()) 
      && !TGA::Collision::checkCollision(subBounds[(ndx + 3) % 4], collidedWith.getBounds()));

   return onlyNdx;
}
