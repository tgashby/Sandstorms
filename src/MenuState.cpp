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
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();
   TGA::Music* music;
   
   menuTexture.loadTexture("resources/ui/menu.png");
   
   music = new TGA::Music("resources/sound/menu.ogg");
   engine->Sounds->addMusic(music, "menu_music");
   
   engine->Sounds->playMusic("menu_music", -1);
}

bool MenuState::update()
{
   TGA::Engine* engine = TGA::Singleton<TGA::Engine>::GetSingletonPtr();

   TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->update();
   if (TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->mouseDown())
   {
      TGA::Vector2D mousePos = TGA::Singleton<TGA::InputManager>::GetSingletonPtr()->getMouseCoords();
      
      if (TGA::Collision::checkCollision(startGameBox, TGA::BoundingBox(static_cast<int>(mousePos.getX()), 
         static_cast<int>(mousePos.getY()), 1, 1)))
      {
         engine->Sounds->pauseMusic("menu_music");
         return false;
      }
      
      if (TGA::Collision::checkCollision(exitGameBox, TGA::BoundingBox(static_cast<int>(mousePos.getX()), 
         static_cast<int>(mousePos.getY()), 1, 1)))
      {
         engine->Sounds->pauseMusic("menu_music");
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
