/**
 * @file Hound.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#include "Hound.h"

Hound::Hound( int health, TGA::Vector2D position, TGA::Vector2D velocity /*= TGA::Vector2D(0, 0)*/, TGA::Vector2D acceleration /*= TGA::Vector2D(0, 1)*/ )
   : Enemy(health, position, velocity, acceleration)
{
   TGA::Texture* runTex = new TGA::Texture("resources/enemies/scraps.png");
   TGA::Animation* runAnim = new TGA::Animation(runTex);
   runAnim->addFrame(TGA::BoundingBox(0, 0, 114, 75), 150);
   runAnim->addFrame(TGA::BoundingBox(115, 0, 117, 75), 150);
   runAnim->addFrame(TGA::BoundingBox(236, 0, 115, 75), 150);
   runAnim->setRepetitions(-1);
   
   animations.insert(std::pair<std::string, TGA::Animation*>("run", runAnim));
   
   currAnimation = animations["run"];
   currAnimationName = "run";
}

void Hound::update()
{
   // AI!
   
   Enemy::update();
}
