/**
 * @file MenuState.cpp
 *
 * @author Tag Ashby
 * @date 8/2012
 * 
 */
#include "MenuState.h"
#include <Vector2D.h>
#include <Singleton.h>
#include <InputManager.h>
#include <Collision.h>
#include <Engine.h>

MenuState::MenuState()
: startGameBox(280, 250, 520, 85)
, exitGameBox(280, 345, 470, 85)
{
   menuTexture.loadTexture("resources/ui/menu.png");
}

bool MenuState::update()
{
   TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->update();
   if (TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->mouseDown())
   {
      TGA::Vector2D mousePos = TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->getMouseCoords();
      
      if (TGA::Collision::checkCollision(startGameBox, TGA::BoundingBox(mousePos.getX(), mousePos.getY(), 1, 1)))
      {
         return false;
      }
      
      if (TGA::Collision::checkCollision(exitGameBox, TGA::BoundingBox(mousePos.getX(), mousePos.getY(), 1, 1)))
      {
         exit(EXIT_SUCCESS);
      }
   }
      
   return true;
}

void MenuState::draw()
{
   menuTexture.draw(0, 0);
   TGA::Singleton<TGA::Engine>::GetSingletonPtr()->Graphics->swapBuffers();
}
