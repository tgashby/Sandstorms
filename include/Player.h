/**
 * @file Player.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include "Character.h"

/**
 * @class Player
 *
 * @brief Represents the player character.
 *
 * Player will contain all methods and information needed 
 * to handle interactions with the player.
 */
class Player : public Character 
{
public:
  /**
  * Player
  *
  * Create a player with an optional initial location.
  * @param TGA::Vector2D position - the player's initial position.
  */
  Player (TGA::Vector2D position = TGA::Vector2D(0,0));
  
  /**
  * @copydoc Character::update()
  */
  virtual void update ();
  
  /**
  * @copydoc Character::draw()
  */
  virtual void draw ();
  
  /**
  * getHealthPercent
  *
  * Gets the player's current health as a percentage.
  * Used for generating the health bar.
  * @return float -
  */
  float getHealthPercent ();

private:
  void jump ();

  bool hasJumped;
  bool hasDoubleJumped;
  Uint64 lastJumpTime;
};

