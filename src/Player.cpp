#include "Player.h"

// TODO: Keep track of which way player is facing

const int PLAYER_MAX_HEALTH = 250;
const double HORIZ_ACCEL = 1;
const double MAX_VEL = 8;
const double JUMP_VEL = -21;

// DEBUG: For simulating life/mana loss
int updateCount = 0;

typedef std::pair<std::string, TGA::Animation*> animPair;

Player::Player( TGA::Vector2D position /*= TGA::Vector2D(0,0)*/ )
   : Character(PLAYER_MAX_HEALTH, position)
{
   maxHealth = PLAYER_MAX_HEALTH;
   mana = maxMana = 100;
   justJumped = hasJumped = hasDoubleJumped = false;

   initAnimations();

   currAnimation = animations["idle"];
   currAnimationName = "idle";
}

void Player::update()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   // DEBUG: Simulate life/mana loss
   updateCount++;
   if (updateCount % 25 == 0)
   {
      //health -= 1;
      //mana -= 1;
      //TGA::Singleton<TGA::Camera>::GetSingletonPtr()->moveOver(-1, 0);
   }

   handleKeyboard();
   
   // If the player is falling (like off a platform)
   if (velocity.getY() > MAX_VEL)
   {
      if (currAnimationName.compare("jump") != 0)
      {
         currAnimation = animations["jump"];
         currAnimationName = "jump";

         currAnimation->setRepetitions(1);
         currAnimation->pause();
      }

      currAnimation->goToFrame(2);
   }

   makeSubBounds();
   Character::update();
}

void Player::draw( float interpolation, float scaleX /*= 1*/, float scaleY /*= 1*/, float rotation /*= 0*/ )
{
   if (velocity.getX() < 0)
   {
      Character::draw(interpolation, -1);
   }
   else
   {
      Character::draw(interpolation);
   }
}

double Player::getHealthPercent()
{
   return ((double)health / maxHealth);
}

void Player::jump()
{
   position.setY(position.getY() - 30); // 30 makes up for the difference in jump frame height
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

void Player::initAnimations()
{
   TGA::Texture* idleTex = new TGA::Texture("../resources/player/idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 138, 200), 1000000);
   idleAnim->setRepetitions(-1);

   TGA::Texture* runTex = new TGA::Texture("../resources/player/run.png");
   TGA::Animation* runAnim = new TGA::Animation(runTex);
   runAnim->addFrame(TGA::BoundingBox(0, 0, 156, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(164, 0, 144, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(312, 0, 116, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(432, 0, 119, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(560, 0, 135, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(699, 0, 155, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(866, 0, 122, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(1010, 0, 111, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(1133, 0, 116, 200), 75);
   runAnim->addFrame(TGA::BoundingBox(1275, 0, 114, 200), 75);
   runAnim->setRepetitions(-1);

   TGA::Texture* jumpTex = new TGA::Texture("../resources/player/jump.png");
   TGA::Animation* jumpAnim = new TGA::Animation(jumpTex);
   jumpAnim->addFrame(TGA::BoundingBox(0, 0, 105, 229), 1);
   jumpAnim->addFrame(TGA::BoundingBox(120, 0, 135, 229), 1);
   jumpAnim->addFrame(TGA::BoundingBox(290, 0, 133, 229), 1);
   jumpAnim->setRepetitions(-1);

   TGA::Texture* punchTex = new TGA::Texture("../resources/player/punch.png");
   TGA::Animation* punchAnim = new TGA::Animation(punchTex);
   punchAnim->addFrame(TGA::BoundingBox(0, 0, 174, 200), 100);
   punchAnim->addFrame(TGA::BoundingBox(175, 0, 133, 200), 100);
   punchAnim->setRepetitions(-1);

   // TODO: Finishing adding player animations

   animations.insert(animations.begin(), animPair("idle", idleAnim));
   animations.insert(animations.begin(), animPair("run", runAnim));
   animations.insert(animations.begin(), animPair("jump", jumpAnim));
   animations.insert(animations.begin(), animPair("punch", punchAnim));
}

void Player::handleKeyboard()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   if (!engine->Input->keyDown(TGA::key_A) && 
      !engine->Input->keyDown(TGA::key_D))
   {
      velocity.setX(0);
      acceleration.setX(0);

      if ((currAnimation->isDone() || currAnimationName.compare("run") == 0) 
         && currAnimationName.compare("idle") != 0)
      {
         currAnimation = animations["idle"];
         currAnimationName = "idle";
      }
   }
   else
   {
      if (engine->Input->keyDown(TGA::key_D))
      {
         if (!hasJumped && currAnimationName.compare("run") != 0)
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
         if (!hasJumped && currAnimationName.compare("run") != 0)
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

            currAnimation->setRepetitions(1);
            currAnimation->pause();
            currAnimation->goToFrame(0);
         }
      }
   }

   if (!engine->Input->keyDown(TGA::key_SPACE))
   {
      justJumped = false;
   }

   if (engine->Input->keyDown(TGA::key_Q))
   {
      if (currAnimationName.compare("punch") != 0)
      {
         currAnimation = animations["punch"];
         currAnimationName = "punch";

         currAnimation->setRepetitions(2);
      }
   }
}

double Player::getManaPercent()
{
   return (double)mana / maxMana;
}

int Player::getArtifactCount()
{
   return 0;//artifacts.size();
}
