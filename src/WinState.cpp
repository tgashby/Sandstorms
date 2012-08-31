#include "WinState.h"
#include <Vector2D.h>
#include <Singleton.h>
#include <InputManager.h>
#include <Collision.h>
#include <Engine.h>

WinState::WinState(bool& playAgain)
: startGameBox(160, 685, 450, 80)
, exitGameBox(880, 685, 160, 70)
, playAgain(playAgain)
{
   winTexture.loadTexture("resources/ui/win.png");
}


WinState::~WinState()
{
}

bool WinState::update()
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

void WinState::draw()
{
   winTexture.draw(0, 0);
   TGA::Singleton<TGA::Engine>::GetSingletonPtr()->Graphics->swapBuffers();
}
