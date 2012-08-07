#include "Player.h"

// TODO: Add kick effects

const int PLAYER_MAX_HEALTH = 250;
const double HORIZ_ACCEL = 1;
const double MAX_VEL = 8;
const double JUMP_VEL = -21;

typedef std::pair<std::string, TGA::Animation*> animPair;

Player::Player( TGA::Vector2D position /*= TGA::Vector2D(0,0)*/ )
   : Character(PLAYER_MAX_HEALTH, position)
{
   maxHealth = PLAYER_MAX_HEALTH;
   mana = maxMana = 100;
   jumping = hasJumped = hasDoubleJumped = false;
   falling = punching = kicking = casting = false;
   facingLeft = false;

   initAnimations();
   addSounds();

   currAnimation = animations["idle"];
   currAnimationName = "idle";
}

void Player::update()
{
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

      falling = true;
   }
   else
   {
      falling = false;
   }

   makeSubBounds();
   Character::update();
}

void Player::draw( float interpolation, float scaleX /*= 1*/, float scaleY /*= 1*/, float rotation /*= 0*/ )
{
   if (facingLeft)
   {
      Character::draw(interpolation, -1);
   }
   else
   {
      Character::draw(interpolation);
   }

   for (std::vector<Artifact*>::iterator i = artifacts.begin(); i < artifacts.end(); i++)
   {
      (*i)->setPosition(getPosition().getX() + getBounds().getWidth() / 2,
         getPosition().getY() + getBounds().getHeight() / 2);
      (*i)->draw();
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
         jumping = false;
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

   if (typeid(collidedWith) == typeid(Artifact))
   {
      artifacts.push_back(&((Artifact&)collidedWith));
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

   TGA::Texture* kickTex = new TGA::Texture("../resources/player/kick.png");
   TGA::Animation* kickAnim = new TGA::Animation(kickTex);
   kickAnim->addFrame(TGA::BoundingBox(0, 0, 165, 200), 500);
   kickAnim->addFrame(TGA::BoundingBox(173, 0, 218, 200), 500);
   kickAnim->setRepetitions(-1);

   TGA::Texture* castTex = new TGA::Texture("../resources/player/cast.png");
   TGA::Animation* castAnim = new TGA::Animation(castTex);
   castAnim->addFrame(TGA::BoundingBox(0, 0, 127, 200), 750);
   castAnim->addFrame(TGA::BoundingBox(130, 0, 156, 200), 250);
   castAnim->setRepetitions(-1);

   TGA::Texture* hurtTex = new TGA::Texture("../resources/player/hurt.png");
   TGA::Animation* hurtAnim = new TGA::Animation(hurtTex);
   hurtAnim->addFrame(TGA::BoundingBox(0, 0, 129, 200), 1000);
   hurtAnim->setRepetitions(-1);

   animations.insert(animations.begin(), animPair("idle", idleAnim));
   animations.insert(animations.begin(), animPair("run", runAnim));
   animations.insert(animations.begin(), animPair("jump", jumpAnim));
   animations.insert(animations.begin(), animPair("punch", punchAnim));
   animations.insert(animations.begin(), animPair("kick", kickAnim));
   animations.insert(animations.begin(), animPair("cast", castAnim));
   animations.insert(animations.begin(), animPair("hurt", hurtAnim));
}

void Player::handleKeyboard()
{
   handleMovements();
   handleAttacks();   
}

double Player::getManaPercent()
{
   return (double)mana / maxMana;
}

int Player::getArtifactCount()
{
   return artifacts.size();
}

void Player::addSounds()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   TGA::Sound* sound;

   sound = new TGA::Sound("../resources/sound/punch.wav");
   engine->Sounds->addSound(sound, "player_punch");
// TODO: Get kick sound
   sound = new TGA::Sound("../resources/sound/kick.wav");
   engine->Sounds->addSound(sound, "player_kick");

   sound = new TGA::Sound("../resources/sound/fireball.wav");
   engine->Sounds->addSound(sound, "player_cast");

   sound = new TGA::Sound("../resources/sound/jump.wav");
   engine->Sounds->addSound(sound, "player_jump");
}

Projectile* Player::generateFireball( bool facingLeft )
{
   TGA::BoundingBox bounds(0, 0, 46, 23);
   std::string fireballTex("../resources/player/fireball.png");
   TGA::Vector2D vel(10.0, 0);
   TGA::Vector2D position(getPosition());
   position.setY(position.getY() + 73);

   if (facingLeft)
   {
      vel.setX(-10.0);
      position.setX(position.getX() - 46);
   }
   else
   {
      position.setX(position.getX() + 156);
   }

   return new Projectile(fireballTex, bounds, position, vel);
}

void Player::handleMovements()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   if (abs(velocity.getX()) > MAX_VEL)
   {
      acceleration.setX(0);
   }

   if (!engine->Input->keyDown(TGA::key_A) && 
      !engine->Input->keyDown(TGA::key_D) && 
      !(jumping || falling || punching || kicking || casting))
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
   else if (!(punching || kicking || casting))
   {
      if (engine->Input->keyDown(TGA::key_D))
      {
         if (!(jumping || falling || hasJumped) && currAnimationName.compare("run") != 0)
         {
            currAnimation = animations["run"];
            currAnimationName = "run";
         }

         if (velocity.getX() < MAX_VEL)
         {
            acceleration.setX(HORIZ_ACCEL);
         }

         facingLeft = false;
      }
      else if (engine->Input->keyDown(TGA::key_A))
      {
         if (!(jumping || falling || hasJumped) && currAnimationName.compare("run") != 0)
         {
            currAnimation = animations["run"];
            currAnimationName = "run";
         }

         if (velocity.getX() > -MAX_VEL)
         {
            acceleration.setX(-HORIZ_ACCEL);
         }

         facingLeft = true;
      }
   }

   if (engine->Input->keyDown(TGA::key_SPACE)
      && !(punching || kicking || casting))
   {
      if (!hasDoubleJumped && !jumping)
      {
         jumping = true;
         jump();

         if (currAnimationName.compare("jump") != 0)
         {
            currAnimation = animations["jump"];
            currAnimationName = "jump";

            currAnimation->setRepetitions(1);
            currAnimation->pause();
            currAnimation->goToFrame(0);

            engine->Sounds->playSound("player_jump", 0);
         }
      }
   }

   if (!engine->Input->keyDown(TGA::key_SPACE))
   {
      jumping = false;
   }
}

void Player::handleAttacks()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   if (!(jumping || falling || hasJumped))
   {
      if (engine->Input->keyDown(TGA::key_Q)
         && !(kicking || casting))
      {
         if (currAnimationName.compare("punch") != 0)
         {
            currAnimation = animations["punch"];
            currAnimationName = "punch";

            currAnimation->setRepetitions(2);

            engine->Sounds->playSound("player_punch", 0);
         }

         punching = true;
         velocity.setX(0);
      }

      if (engine->Input->keyDown(TGA::key_E)
         && !(punching || casting))
      {
         if (currAnimationName.compare("kick") != 0)
         {
            currAnimation = animations["kick"];
            currAnimationName = "kick";

            currAnimation->setRepetitions(1);

            engine->Sounds->playSound("player_kick", 0);
         }

         kicking = true;
         velocity.setX(0);
      }

      if (engine->Input->keyDown(TGA::key_F)
         && !(punching || kicking))
      {
         if (currAnimationName.compare("cast") != 0)
         {
            casting = true;
            currAnimation = animations["cast"];
            currAnimationName = "cast";

            currAnimation->setRepetitions(1);

            engine->Sounds->playSound("player_cast", 0);
         }
         velocity.setX(0);
      }
   }

   if (currAnimationName.compare("cast") == 0)
   {
      if (currAnimation->getFrameNum() == 1 && casting)
      {
         TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->addProjectile(
            generateFireball(facingLeft));
         casting = false;
      }
   }

   if (currAnimationName.compare("kick") == 0)
   {
      if (currAnimation->getFrameNum() == 1 && kicking)
      {
         engine->Sounds->playSound("player_kick", 0);
         kicking = false;
      }
   }

   if (currAnimationName.compare("punch") == 0)
   {
      punching = !currAnimation->isDone();
   }
}
