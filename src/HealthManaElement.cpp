/**
 * @file HealthManaElement.cpp
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */

#include "HealthManaElement.h"

const int BAR_HEIGHT = 24;

HealthManaElement::HealthManaElement()
   : containerPos(10, 10)
   , healthPos(35, 25)
   , manaPos(55, 56)
{
   healthBar = new TGA::Texture("resources/ui/health.png");
   manaBar = new TGA::Texture("resources/ui/mana.png");
   container = new TGA::Texture("resources/ui/healthManaContainer.png");
}

void HealthManaElement::update( double healthPercent, double manaPercent )
{
   TGA::Camera* camera = TGA::Singleton<TGA::Camera>::GetSingletonPtr();
   
   this->healthPercent = healthPercent;
   this->manaPercent = manaPercent;
   
   healthPos.setX(camera->getX() + 35);
   manaPos.setX(camera->getX() + 55);
   containerPos.setX(camera->getX() + 10);
}

void HealthManaElement::draw()
{
   healthBar->drawSection(static_cast<float>(healthPos.getX()), static_cast<float>(healthPos.getY()),
                          0, 0, static_cast<int>(healthPercent * healthBar->getWidth()), BAR_HEIGHT);
   manaBar->drawSection(static_cast<float>(manaPos.getX()), static_cast<float>(manaPos.getY()),
                        0, 0, static_cast<int>(manaPercent * manaBar->getWidth()), BAR_HEIGHT);
   
   container->draw(static_cast<float>(containerPos.getX()), static_cast<float>(containerPos.getY()));
}
