/**
 * @file Warrior.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#include "Warrior.h"
#include "Attack.h"

const int ATTACK_DAMAGE = 15;

Warrior::Warrior(int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/ )
   : Enemy(health, position, velocity, acceleration)
{
   TGA::Texture* walkTex = new TGA::Texture("resources/enemies/warrior_walk.png");
   TGA::Animation* walkAnim = new TGA::Animation(walkTex);
   walkAnim->addFrame(TGA::BoundingBox(0, 0, 171, 266), 75);
   walkAnim->addFrame(TGA::BoundingBox(185, 0, 165, 266), 75);
   walkAnim->addFrame(TGA::BoundingBox(380, 0, 168, 266), 75);
   walkAnim->addFrame(TGA::BoundingBox(568, 0, 165, 266), 75);
   walkAnim->setRepetitions(-1);
   
   TGA::Texture* attackTex = new TGA::Texture("resources/enemies/warrior_attack.png");
   TGA::Animation* attackAnim = new TGA::Animation(attackTex);
   attackAnim->addFrame(TGA::BoundingBox(0, 0, 244, 266), 500);
   attackAnim->addFrame(TGA::BoundingBox(248, 0, 239, 266), 500);
   attackAnim->setRepetitions(-1);
   
   TGA::Texture* idleTex = new TGA::Texture("resources/enemies/warrior_idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 182, 266), 75);
   idleAnim->setRepetitions(-1);
   
   animations.insert(std::pair<std::string, TGA::Animation*>("walk", walkAnim));
   animations.insert(std::pair<std::string, TGA::Animation*>("attack", attackAnim));
   animations.insert(std::pair<std::string, TGA::Animation*>("idle", idleAnim));
   
   currAnimation = animations["idle"];
   currAnimationName = "idle";
   
   setLeftBound(position.getX() - 300, 0);
   setRightBound(position.getX() + 300, 0);
   
   originalSpeed = abs(velocity.getX());
   attacking = secondPunch = false;
   
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   TGA::Sound* sound;
   
   sound = new TGA::Sound("resources/sound/warrior.wav");
   engine->Sounds->addSound(sound, "warrior_punch");
}

void Warrior::update(TGA::Vector2D playerPosition)
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   
   // AI!
   double distToPlayer = position.distanceFrom(playerPosition);
   bool playerOnLeft = playerPosition.getX() < position.getX();
   
   facingLeft = velocity.getX() < 0;
   
   if (distToPlayer > 500)
   {
      if (currAnimationName.compare("walk") != 0)
      {
         currAnimation = animations["walk"];
         currAnimationName = "walk";
      }
      
      velocity.setX(velocity.getX() < 0 ? -originalSpeed : originalSpeed);
      if ((position.getX() < leftBound.getX() && velocity.getX() < 0)
          || (position.getX() > rightBound.getX() && velocity.getX() > 0))
      {
         velocity.setX(-velocity.getX());
      }
   }
   else if ((distToPlayer > 100 && playerOnLeft) || (distToPlayer > 200 && !playerOnLeft))
   {
      if (currAnimationName.compare("walk") != 0)
      {
         currAnimation = animations["walk"];
         currAnimationName = "walk";
      }
      
      // Switch direction and speed for the chase!
      velocity.setX(originalSpeed + 1.0);
      
      if ((playerOnLeft && velocity.getX() > 0) || (!playerOnLeft && velocity.getX() < 0))
      {
         velocity.setX(-velocity.getX());
      }
   }
   else
   {
      if (currAnimationName.compare("attack") != 0 || !attacking)
      {
         attacking = true;
         secondPunch = false;
         currAnimation = animations["attack"];
         currAnimationName = "attack";
         
         currAnimation->setRepetitions(1);
         engine->Sounds->playSound("warrior_punch", 0);
         attack(playerOnLeft);
      }
      
      velocity.setX(0);
      
      facingLeft = playerOnLeft;
   }
   
   if (currAnimationName.compare("attack") == 0)
   {
      if (currAnimation->getFrameNum() == 1 && !secondPunch)
      {
         attack(playerOnLeft);
         secondPunch = true;
         engine->Sounds->playSound("warrior_punch", 0);
      }
      attacking = !currAnimation->isDone();
   }
   else
   {
      attacking = false;
   }
   
   Enemy::update(playerPosition);
}

void Warrior::attack(bool playerOnLeft)
{
   if (playerOnLeft)
   {
      new Attack(ATTACK_DAMAGE,
       TGA::BoundingBox(static_cast<int>(position.getX()), 
        static_cast<int>(position.getY()),
        static_cast<int>(currAnimation->getCurrentFrameDimensions().getWidth() / 2),
        100),
      2, this);
   }
   else
   {
      new Attack(ATTACK_DAMAGE,
                 TGA::BoundingBox(static_cast<int>(position.getX() + currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  static_cast<int>(position.getY()),
                                  static_cast<int>(currAnimation->getCurrentFrameDimensions().getWidth() / 2),
                                  100),
                 2, this);
   }
}