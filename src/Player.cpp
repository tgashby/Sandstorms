#include "Player.h"

// BUG: Game Speed/Player Speed is not doing correct time-based movements.
// TODO: Jump needs to be overhauled. 1. Holding space runs animation forever. 2. Animation doesn't reflect action.

const int PLAYER_MAX_HEALTH = 250;
const double HORIZ_ACCEL = 1;
const double MAX_VEL = 8;
const double JUMP_VEL = -27;

typedef std::pair<std::string, TGA::Animation*> animPair;

Player::Player( TGA::Vector2D position /*= TGA::Vector2D(0,0)*/ )
   : Character(PLAYER_MAX_HEALTH, position)
{
   maxHealth = PLAYER_MAX_HEALTH;
   justJumped = hasJumped = hasDoubleJumped = false;

   TGA::Texture* idleTex = new TGA::Texture("../resources/player/idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 138, 202), 1000000);
   idleAnim->setRepetitions(-1);

   TGA::Texture* runTex = new TGA::Texture("../resources/player/run.png");
   TGA::Animation* runAnim = new TGA::Animation(runTex);
   runAnim->addFrame(TGA::BoundingBox(0, 0, 172, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(172, 0, 160, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(332, 0, 128, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(460, 0, 130, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(595, 0, 150, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(745, 0, 180, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(925, 0, 150, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(1075, 0, 135, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(1210, 0, 145, 214), 75);
   runAnim->addFrame(TGA::BoundingBox(1355, 0, 133, 214), 75);
   runAnim->setRepetitions(-1);

   TGA::Texture* jumpTex = new TGA::Texture("../resources/player/jump.png");
   TGA::Animation* jumpAnim = new TGA::Animation(jumpTex);
   jumpAnim->addFrame(TGA::BoundingBox(0, 0, 105, 229), 500);
   jumpAnim->addFrame(TGA::BoundingBox(120, 0, 135, 229), 500);
   jumpAnim->addFrame(TGA::BoundingBox(290, 0, 133, 229), 500);
   jumpAnim->setRepetitions(-1);

   // TODO: Finishing adding player animations

   animations.insert(animations.begin(), animPair("idle", idleAnim));
   animations.insert(animations.begin(), animPair("run", runAnim));
   animations.insert(animations.begin(), animPair("jump", jumpAnim));

   currAnimation = idleAnim;
   currAnimationName = "idle";
}

void Player::update()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   
   if (!engine->Input->keyDown(TGA::key_A) && 
       !engine->Input->keyDown(TGA::key_D))
   {
      velocity.setX(0);
      acceleration.setX(0);
      
      if (!justJumped && currAnimationName.compare("idle") != 0)
      {
         currAnimation = animations["idle"];
         currAnimationName = "idle";
      }
   }
   else
   {
      if (engine->Input->keyDown(TGA::key_D))
      {
         if (!justJumped && currAnimationName.compare("run") != 0)
         {
            currAnimation = animations["run"];
            currAnimationName = "run";
         }

         if (velocity.getX() < MAX_VEL)
         {
            acceleration.setX(HORIZ_ACCEL);
         }
         else
         {
            acceleration.setX(0);
         }
      }
      else if (engine->Input->keyDown(TGA::key_A))
      {
         if (!justJumped && currAnimationName.compare("run") != 0)
         {
            currAnimation = animations["run"];
            currAnimationName = "run";
         }

         if (velocity.getX() > -MAX_VEL)
         {
            acceleration.setX(-HORIZ_ACCEL);
         }
         else
         {
            acceleration.setX(0);
         }
      }
   }

   if (engine->Input->keyDown(TGA::key_SPACE))
   {
      if (!hasDoubleJumped && !justJumped)
      {
         justJumped = true;
         jump();

         if (currAnimationName.compare("jump") != 0)
         {
            currAnimation = animations["jump"];
            currAnimationName = "jump";
         }
      }
   }

   if (!engine->Input->keyDown(TGA::key_SPACE))
   {
      justJumped = false;
   }

   makeSubBounds();

   Character::update();
}

void Player::draw(float interpolation, bool flipped /* = false */)
{
   if (velocity.getX() < 0)
   {
      Character::draw(interpolation, true);
   }
   else
   {
      Character::draw(interpolation);
   }
}

float Player::getHealthPercent()
{
   return ((float)health / maxHealth);
}

void Player::jump()
{
   position.setY(position.getY() - 29); // 29 makes up for the difference in jump animation height
   velocity.setY(JUMP_VEL);

   if (!hasJumped)
   {
      hasJumped = true;
   }
   else if (!hasDoubleJumped)
   {
      hasDoubleJumped = true;
   }
}

void Player::handleCollision( TGA::Collidable& collidedWith )
{
   bool onlyHeadColliding = collidedWithOnlySubBound(0, collidedWith);
   bool onlyLeftColliding = collidedWithOnlySubBound(1, collidedWith);
   bool onlyRightColliding = collidedWithOnlySubBound(2, collidedWith);
   bool onlyFeetColliding = collidedWithOnlySubBound(3, collidedWith);

   if (typeid(collidedWith) == typeid(Platform))
   {
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

         hasJumped = hasDoubleJumped = false;
      }
      else // More than one sub-boundary
      {
         // TODO: Implement more than one collision
         std::cout << "Multiple Collision:\n";
         if (TGA::Collision::checkCollision(subBounds[0], collidedWith.getBounds()))
         {
            std::cout << "Head\n";
         }
         if (TGA::Collision::checkCollision(subBounds[1], collidedWith.getBounds()))
         {
            std::cout << "Left\n";
         }
         if (TGA::Collision::checkCollision(subBounds[2], collidedWith.getBounds()))
         {
            std::cout << "Right\n";
         }
         if (TGA::Collision::checkCollision(subBounds[3], collidedWith.getBounds()))
         {
            std::cout << "Feet\n";
         }
      }
   }
}

void Player::makeSubBounds()
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
   subBounds[3] = TGA::BoundingBox((int)position.getX(), (int)position.getY() + (int)(frameHeight * 0.8) + 1, frameWidth, frameHeight / 5 + 1);
}

bool Player::collidedWithOnlySubBound(int ndx, TGA::Collidable& collidedWith)
{
   bool onlyNdx = (TGA::Collision::checkCollision(subBounds[ndx], collidedWith.getBounds()) 
      && !TGA::Collision::checkCollision(subBounds[(ndx + 1) % 4], collidedWith.getBounds()) 
      && !TGA::Collision::checkCollision(subBounds[(ndx + 2) % 4], collidedWith.getBounds()) 
      && !TGA::Collision::checkCollision(subBounds[(ndx + 3) % 4], collidedWith.getBounds()));

   return onlyNdx;
}
