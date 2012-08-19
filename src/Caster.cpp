/**
 * @file Caster.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#include "Caster.h"

Caster::Caster(int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/)
   : Enemy(health, position, velocity, acceleration)
{   
   TGA::Texture* attackTex = new TGA::Texture("resources/enemies/caster_attack.png");
   TGA::Animation* attackAnim = new TGA::Animation(attackTex);
   attackAnim->addFrame(TGA::BoundingBox(0, 0, 140, 200), 75);
   attackAnim->addFrame(TGA::BoundingBox(156, 0, 179, 200), 75);
   attackAnim->setRepetitions(-1);
   
   TGA::Texture* idleTex = new TGA::Texture("resources/enemies/caster_idle.png");
   TGA::Animation* idleAnim = new TGA::Animation(idleTex);
   idleAnim->addFrame(TGA::BoundingBox(0, 0, 145, 200), 75);
   idleAnim->setRepetitions(-1);
   
   animations.insert(std::pair<std::string, TGA::Animation*>("attack", attackAnim));
   animations.insert(std::pair<std::string, TGA::Animation*>("idle", idleAnim));
   
   currAnimation = animations["idle"];
   currAnimationName = "idle";
}

void Caster::update()
{
   // AI!
   
   Enemy::update();
}
