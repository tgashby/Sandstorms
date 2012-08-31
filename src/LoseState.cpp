/**
 * @file LoseState.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */

#include "LoseState.h"
#include <Vector2D.h>
#include <Singleton.h>
#include <InputManager.h>
#include <Collision.h>
#include <Engine.h>

LoseState::LoseState(bool& playAgain)
: startGameBox(360, 660, 205, 82)
, exitGameBox(720, 660, 158, 82)
, playAgain(playAgain)
{
   loseTexture.loadTexture("resources/ui/lose.png");
}


LoseState::~LoseState()
{
}

bool LoseState::update()
{
   TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->update();
   if (TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->mouseDown())
   {
      TGA::Vector2D mousePos = TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->getMouseCoords();

      if (TGA::Collision::checkCollision(startGameBox, TGA::BoundingBox(static_cast<int>(mousePos.getX()), 
         static_cast<int>(mousePos.getY()), 1, 1)))
      {
         playAgain = true;
         return false;
      }

      if (TGA::Collision::checkCollision(exitGameBox, TGA::BoundingBox(static_cast<int>(mousePos.getX()), 
         static_cast<int>(mousePos.getY()), 1, 1)))
      {
         playAgain = false;
         return false;
      }
   }

   return true;
}

void LoseState::draw()
{
   loseTexture.draw(0, 0);
   TGA::Singleton<TGA::Engine>::GetSingletonPtr()->Graphics->swapBuffers();
}
