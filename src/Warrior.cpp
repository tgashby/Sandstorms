/**
 * @file Warrior.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#include "Warrior.h"

Warrior::Warrior( int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/ )
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
   attackAnim->addFrame(TGA::BoundingBox(0, 0, 244, 266), 75);
   attackAnim->addFrame(TGA::BoundingBox(248, 0, 239, 266), 75);
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
}

void Warrior::update()
{
   // AI!
   
   Enemy::update();
}
