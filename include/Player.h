/**
 * @file Player.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include "Character.h"
#include <Timer.h>
#include <Collision.h>
#include "Platform.h"

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
  * @copydoc Character::update(Uint32 dt)
  */
  virtual void update (Uint32 dt);

  /**
   * @copydoc Character::draw(bool flipped)
   */
  virtual void draw(bool flipped = false);
  
  /**
  * getHealthPercent
  *
  * Gets the player's current health as a percentage.
  * Used for generating the health bar.
  * @return float -
  */
  float getHealthPercent ();

  /**
   * handleCollision
   *
   * Update the state of the Player based on what it collided with.
   * @param TGA::Collidable collidedWith - the entity collided with
   */
  virtual void handleCollision (TGA::Collidable& collidedWith);

private:
  void jump ();
  void makeSubBounds();
  bool collidedWithOnlySubBound(int ndx, TGA::Collidable& collidedWith);

  int maxHealth;
  bool justJumped;
  bool hasJumped;
  bool hasDoubleJumped;
  TGA::BoundingBox subBounds[4];
  std::string currAnimationName;
};

