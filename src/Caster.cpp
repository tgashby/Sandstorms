/**
 * @file Caster.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#include "Caster.h"
#include "ProjectileFactory.h"

Caster::Caster(int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/)
   : Enemy(health, position, velocity, acceleration)
{
   TGA::Texture* attackTex = new TGA::Texture("resources/enemies/caster_attack.png");
   TGA::Animation* attackAnim = new TGA::Animation(attackTex);
   attackAnim->addFrame(TGA::BoundingBox(0, 0, 140, 200), 750);
   attackAnim->addFrame(TGA::BoundingBox(156, 0, 179, 200), 250);
   attackAnim->setRepetitions(-1);
   
   TGA::Texture* idleTex = new TGA::Texture("resources/enemies/caster_idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 145, 200), 75);
   idleAnim->setRepetitions(-1);
   
   animations.insert(std::pair<std::string, TGA::Animation*>("attack", attackAnim));
   animations.insert(std::pair<std::string, TGA::Animation*>("idle", idleAnim));
   
   currAnimation = animations["idle"];
   currAnimationName = "idle";
   
   setLeftBound(position.getX() - 300, 0);
   setRightBound(position.getX() + 300, 0);
   
   attacking = casted = false;
   
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   TGA::Sound* sound;
   
   sound = new TGA::Sound("resources/sound/caster.wav");
   engine->Sounds->addSound(sound, "caster_cast");
}

void Caster::update(TGA::Vector2D playerPosition)
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   // AI!
   double distToPlayer = position.distanceFrom(playerPosition);
   
   facingLeft = velocity.getX() < 0;
   
   if (distToPlayer > 800)
   {
      if (currAnimationName.compare("idle") != 0)
      {
         currAnimation = animations["idle"];
         currAnimationName = "idle";
      }
      
      if (position.getX() < leftBound.getX() || position.getX() > rightBound.getX())
      {
         velocity.setX(-velocity.getX());
      }
   }
   else
   {
      if (currAnimationName.compare("attack") != 0 || !attacking)
      {
         attacking = true;
         casted = false;
         currAnimation = animations["attack"];
         currAnimationName = "attack";
         
         currAnimation->setRepetitions(1);
         engine->Sounds->playSound("caster_cast", 0);
      }
      
      velocity.setX(0);
      
      facingLeft = playerPosition.getX() < position.getX();
   }
   
   if (currAnimationName.compare("attack") == 0)
   {
      if (currAnimation->getFrameNum() == 1 && !casted)
      {
         attack(playerPosition);
         casted = true;
      }
      attacking = !currAnimation->isDone();
   }
   else
   {
      attacking = false;
   }
   
   Enemy::update(playerPosition);
}

void Caster::attack(TGA::Vector2D playerPosition)
{

   bool playerOnLeft = playerPosition.getX() < position.getX();
   int boundWidth, boundHeight;
   std::string projStr;
   
   TGA::Vector2D boltPos(position), boltVel(0, 0);

   if (abs(playerPosition.getY() - position.getY()) > 210)
   {
      boltPos.setX(boltPos.getX() + 50);
      boundWidth = 34;
      boundHeight = 61;

      // Player below
      if (playerPosition.getY() > position.getY())
      {
         boltVel.setY(10.0);
         boltPos.setY(boltPos.getY() + 200);
         projStr = "resources/enemies/casterProjDown.png";
      }
      else
      {
         boltVel.setY(-10.0);
         boltPos.setY(boltPos.getY() - 62);
         projStr = "resources/enemies/casterProjUp.png";
      }
   }
   else
   {
      boltPos.setY(boltPos.getY() + 59);
      projStr = "resources/enemies/casterProj.png";
      boundWidth = 61;
      boundHeight = 34;

      if (playerOnLeft)
      {
         boltVel.setX(-10.0);
         boltPos.setX(boltPos.getX() - 62);
      }
      else
      {
         boltVel.setX(10.0);
         boltPos.setX(boltPos.getX() + 179);
      }
   }
   
   
   TGA::Singleton<ProjectileFactory>::GetSingletonPtr()->addProjectile(new Projectile(30, projStr, TGA::BoundingBox(static_cast<int>(boltPos.getX()), static_cast<int>(boltPos.getY()), boundWidth, boundHeight), boltPos, boltVel));
}