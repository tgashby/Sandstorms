#include "Player.h"
#include "Projectile.h"
#include "ProjectileFactory.h"
#include "Platform.h"
#include "Artifact.h"
#include "Caster.h"
#include "Warrior.h"
#include "Hound.h"
#include "Attack.h"

const int PLAYER_MAX_HEALTH = 250;
const int PLAYER_MAX_MANA = 100;
const double HORIZ_ACCEL = 1;
const double MAX_VEL = 8;
const double JUMP_VEL = -21;
const int FIREBALL_COST = 20, FIREBALL_DAMAGE = 45;
const int PUNCH_DAMAGE = 20, KICK_DAMAGE = 20;
int manaCycle = 0;
int hurtCycle = 0;

typedef std::pair<std::string, TGA::Animation*> animPair;

Player::Player( TGA::Vector2D position /*= TGA::Vector2D(0,0)*/ )
   : Character(PLAYER_MAX_HEALTH, position)
{
   maxHealth = PLAYER_MAX_HEALTH;
   maxMana = PLAYER_MAX_MANA;
   
   cleanSlate();
   
   initAnimations();
   addSounds();
   
   currAnimation = animations["idle"];
   currAnimationName = "idle";
}

void Player::update()
{
   if (abs(velocity.getX()) > MAX_VEL)
   {
      acceleration.setX(0);
   }
   
   handleKeyboard();
   
//   assert(abs(velocity.getX()) < MAX_VEL + 1.5f);
   
   // If the player is falling (like off a platform)
   if (velocity.getY() > MAX_VEL && !hurting)
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
   
   // Regenerating Mana
   manaCycle++;
   
   if (manaCycle > 50)
   {
      mana += 1;
      manaCycle = 0;
      
      if (mana > maxMana)
      {
         mana = maxMana;
      }
   }
   
   // Pause between being able to be injured by colliding with enemies
   if (!canBeHurt)
   {
      hurtCycle++;
      
      if (hurtCycle > 100)
      {
         canBeHurt = true;
         hurtCycle = 0;
      }
   }
   
   if (currAnimationName.compare("hurt") == 0)
   {
      hurting = !currAnimation->isDone();
   }
   
   makeSubBounds();
   Character::update();
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
   if (typeid(collidedWith) == typeid(Platform))
   {
      collideWithPlatform((Platform&)collidedWith);
      
      if (collidedWithOnlySubBound(3, collidedWith)) {
         hasJumped = hasDoubleJumped = false;
         jumping = false;
      }
   }
   
   if (typeid(collidedWith) == typeid(Artifact))
   {
      artifactCount++;
   }
   
   if (typeid(collidedWith) == typeid(Caster)
       || typeid(collidedWith) == typeid(Warrior)
       || typeid(collidedWith) == typeid(Hound))
   {
      if (!(punching || kicking || casting)
          && currAnimationName.compare("hurt") != 0
          && canBeHurt)
      {
         hurting = true;
         canBeHurt = false;
         takeDamage(10);
      }
   }
}

void Player::takeDamage(int howMuch)
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   
   if (!(punching || kicking || casting)
       && currAnimationName.compare("hurt") != 0)
   {
      currAnimation = animations["hurt"];
      currAnimationName = "hurt";
      
      currAnimation->setRepetitions(1);
      
      engine->Sounds->playSound("player_hurt", 0);
   }
   
   velocity.setX(0);
   acceleration.setX(0);
   
   Character::takeDamage(howMuch);
}

void Player::reset()
{
   position.setX(0);
   position.setY(400);
   
   cleanSlate();
}

void Player::cleanSlate()
{
   health = PLAYER_MAX_HEALTH;
   mana = PLAYER_MAX_MANA;
   jumping = hasJumped = hasDoubleJumped = false;
   falling = punching = kicking = casting = hurting = false;
   runPlaying = kickPlaying = castPlaying = false;
   facingLeft = true; // This is flipped because the original image is flipped
   canBeHurt = true;
   artifactCount = 0;
}

void Player::initAnimations()
{
   TGA::Texture* idleTex = new TGA::Texture("resources/player/idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 138, 200), 1000000);
   idleAnim->setRepetitions(-1);
   
   TGA::Texture* runTex = new TGA::Texture("resources/player/run.png");
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
   
   TGA::Texture* jumpTex = new TGA::Texture("resources/player/jump.png");
   TGA::Animation* jumpAnim = new TGA::Animation(jumpTex);
   jumpAnim->addFrame(TGA::BoundingBox(0, 0, 105, 229), 1);
   jumpAnim->addFrame(TGA::BoundingBox(120, 0, 135, 229), 1);
   jumpAnim->addFrame(TGA::BoundingBox(290, 0, 133, 229), 1);
   jumpAnim->setRepetitions(-1);
   
   TGA::Texture* punchTex = new TGA::Texture("resources/player/punch.png");
   TGA::Animation* punchAnim = new TGA::Animation(punchTex);
   punchAnim->addFrame(TGA::BoundingBox(0, 0, 174, 200), 100);
   punchAnim->addFrame(TGA::BoundingBox(175, 0, 133, 200), 100);
   punchAnim->setRepetitions(-1);
   
   TGA::Texture* kickTex = new TGA::Texture("resources/player/kick.png");
   TGA::Animation* kickAnim = new TGA::Animation(kickTex);
   kickAnim->addFrame(TGA::BoundingBox(0, 0, 165, 200), 500);
   kickAnim->addFrame(TGA::BoundingBox(173, 0, 218, 200), 500);
   kickAnim->setRepetitions(-1);
   
   TGA::Texture* castTex = new TGA::Texture("resources/player/cast.png");
   TGA::Animation* castAnim = new TGA::Animation(castTex);
   castAnim->addFrame(TGA::BoundingBox(0, 0, 127, 200), 750);
   castAnim->addFrame(TGA::BoundingBox(130, 0, 156, 200), 250);
   castAnim->setRepetitions(-1);
   
   TGA::Texture* hurtTex = new TGA::Texture("resources/player/hurt.png");
   TGA::Animation* hurtAnim = new TGA::Animation(hurtTex);
   hurtAnim->addFrame(TGA::BoundingBox(0, 0, 129, 200), 500);
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
   if (!hurting)
   {
      handleMovements();
      handleAttacks();
   }
}

double Player::getManaPercent()
{
   return (double)mana / maxMana;
}

int Player::getArtifactCount()
{
   return artifactCount;
}

void Player::addHealth(int howMuch)
{
   health += howMuch;
   
   if (health > maxHealth)
   {
      health = maxHealth;
   }
}

void Player::addMana(int howMuch)
{
   mana += howMuch;
   
   if (mana > maxMana)
   {
      mana = maxMana;
   }
}

void Player::addSounds()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   TGA::Sound* sound;
   
   sound = new TGA::Sound("resources/sound/punch.wav");
   engine->Sounds->addSound(sound, "player_punch");
   
   sound = new TGA::Sound("resources/sound/kick.wav");
   engine->Sounds->addSound(sound, "player_kick");
   
   sound = new TGA::Sound("resources/sound/fireball.wav");
   engine->Sounds->addSound(sound, "player_cast");
   
   sound = new TGA::Sound("resources/sound/jump.wav");
   engine->Sounds->addSound(sound, "player_jump");
   
   sound = new TGA::Sound("resources/sound/hurt.wav");
   engine->Sounds->addSound(sound, "player_hurt");
   
   sound = new TGA::Sound("resources/sound/run.wav");
   engine->Sounds->addSound(sound, "player_run");

   sound = new TGA::Sound("resources/sound/attack.wav");
   engine->Sounds->addSound(sound, "player_attack");
}

Projectile* Player::generateFireball(bool facingLeft)
{
   TGA::BoundingBox bounds(0, 0, 46, 23);
   std::string fireballTex("resources/player/fireball.png");
   TGA::Vector2D vel(10.0, 0);
   TGA::Vector2D position(getPosition());
   position.setY(position.getY() + 73);
   bounds.setY(static_cast<int>(position.getY()));
   
   if (!facingLeft)
   {
      vel.setX(-10.0);
      position.setX(position.getX() - 46);
   }
   else
   {
      position.setX(position.getX() + 156);
   }
   
   bounds.setX(static_cast<int>(position.getX()));
   
   return new Projectile(FIREBALL_DAMAGE, fireballTex, bounds, position, vel);
}

void Player::handleMovements()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   
   if (!engine->Input->keyDown(TGA::key_A) &&
       !engine->Input->keyDown(TGA::key_D) &&
       !engine->Input->keyDown(TGA::key_LEFT_ARROW) &&
       !engine->Input->keyDown(TGA::key_RIGHT_ARROW) &&
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
      
      if (runPlaying)
      {
         engine->Sounds->pauseSound("player_run");
         runPlaying = false;
      }
   }
   else if (!(punching || kicking || casting))
   {
      if (engine->Input->keyDown(TGA::key_D) || engine->Input->keyDown(TGA::key_RIGHT_ARROW))
      {
         if (!(jumping || falling || hasJumped) && currAnimationName.compare("run") != 0)
         {
            currAnimation = animations["run"];
            currAnimationName = "run";
            
            if (!runPlaying)
            {
               engine->Sounds->playSound("player_run", -1);
               runPlaying = true;
            }
         }
         else if (jumping || falling || hasJumped)
         {
            if (runPlaying)
            {
               engine->Sounds->pauseSound("player_run");
               runPlaying = false;
            }
         }
         
         if (velocity.getX() < MAX_VEL)
         {
            acceleration.setX(HORIZ_ACCEL);
         }
         
         facingLeft = true; // This is flipped because the original image is flipped
      }
      else if (engine->Input->keyDown(TGA::key_A) || engine->Input->keyDown(TGA::key_LEFT_ARROW))
      {
         if (!(jumping || falling || hasJumped) && currAnimationName.compare("run") != 0)
         {
            currAnimation = animations["run"];
            currAnimationName = "run";
            
            if (!runPlaying)
            {
               engine->Sounds->playSound("player_run", -1);
               runPlaying = true;
            }
         }
         else if (jumping || falling || hasJumped)
         {
            if (runPlaying)
            {
               engine->Sounds->pauseSound("player_run");
               runPlaying = false;
            }
         }
         
         if (velocity.getX() > -MAX_VEL)
         {
            acceleration.setX(-HORIZ_ACCEL);
         }
         
         facingLeft = false; // This is flipped because the original image is flipped
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

   if (punching || kicking || casting)
   {
      velocity.setX(0);
      acceleration.setX(0);
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
            punching = true;
            currAnimation = animations["punch"];
            currAnimationName = "punch";
            
            currAnimation->setRepetitions(2);
            
            engine->Sounds->playSound("player_punch", 0);
            
            punchAttack();
         }
         
         velocity.setX(0);
      }
      
      if (engine->Input->keyDown(TGA::key_E)
          && !(punching || casting))
      {
         if (currAnimationName.compare("kick") != 0)
         {
            kicking = true;
            kickPlaying = false;
            currAnimation = animations["kick"];
            currAnimationName = "kick";
            
            currAnimation->setRepetitions(1);
            
            engine->Sounds->playSound("player_kick", 0);
            
            kickAttack();
         }
         
         velocity.setX(0);
      }
      
      if (mana > FIREBALL_COST)
      {
         if (engine->Input->keyDown(TGA::key_F)
             && !(punching || kicking))
         {
            if (currAnimationName.compare("cast") != 0)
            {
               casting = true;
               castPlaying = false;
               currAnimation = animations["cast"];
               currAnimationName = "cast";
               
               currAnimation->setRepetitions(1);
               
               engine->Sounds->playSound("player_cast", 0);
            }
            velocity.setX(0);
         }
      }
   }
   
   if (currAnimationName.compare("cast") == 0)
   {
      if (currAnimation->getFrameNum() == 1 && casting && !castPlaying)
      {
         TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->addProjectile(
                                                                             generateFireball(facingLeft));
         mana -= FIREBALL_COST;
         castPlaying = true;
      }
      
      casting = !currAnimation->isDone();
   }
   
   if (currAnimationName.compare("kick") == 0)
   {
      if (currAnimation->getFrameNum() == 1 && kicking && !kickPlaying)
      {
         engine->Sounds->playSound("player_kick", 0);
         kickPlaying = true;
         
         kickAttack();
      }
      kicking = !currAnimation->isDone();
   }
   
   if (currAnimationName.compare("punch") == 0)
   {
      punching = !currAnimation->isDone();
   }
}

void Player::punchAttack()
{
   if (facingLeft)
   {
      new Attack(PUNCH_DAMAGE,
                 TGA::BoundingBox(static_cast<int>(position.getX() + currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  static_cast<int>(position.getY()),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  100),
                 2, this);
   }
   else
   {
      new Attack(PUNCH_DAMAGE,
                 TGA::BoundingBox(static_cast<int>(position.getX()), static_cast<int>(position.getY()),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  100),
                 2, this);
   }
}

void Player::kickAttack()
{
   if (facingLeft)
   {
      new Attack(KICK_DAMAGE,
                 TGA::BoundingBox(static_cast<int>(position.getX() + currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  static_cast<int>(position.getY()),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getHeight())),
                 2, this);
   }
   else
   {
      new Attack(KICK_DAMAGE,
                 TGA::BoundingBox(static_cast<int>(position.getX()), static_cast<int>(position.getY()),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getHeight())),
                 2, this);
   }
}