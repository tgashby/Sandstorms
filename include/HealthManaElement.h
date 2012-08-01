/**
 * @file HealthManaElement.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include "HUDElement.h"

/**
 * @class HealthManaElement
 *
 * @brief A HUDElement that holds the player's
 * health and mana values as bars of variable length.
 *
 */
class HealthManaElement
{
public:
  /**
  * HealthManaElement
  *
  * Creates a new HealthManaElement, there should never be more than one of these.
  */
  HealthManaElement (std::string baseTexStr);

  /**
  * update
  *
  * Update the health and mana bar lengths.
  * @param healthPercent - the percent of health remaining
  * @param manaPercent - the percent of mana remaining
  */
  void update (double healthPercent, double manaPercent);
  
  /**
  * draw
  *
  * Draw the container and the bars with their relative lengths.
  */
  virtual void draw ();


  // THIS IS CLEARY A DESIGN ISSUE
  virtual void update() {}

private:
   TGA::Texture* healthBar;
   TGA::Texture* manaBar;
   TGA::Texture* container;
   TGA::Vector2D healthPos, manaPos, containerPos;
   double healthPercent;
   double manaPercent;
};

