/**
 * @file Player.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <Timer.h>
#include <Collision.h>
#include <Camera.h>
#include "Character.h"
#include "Platform.h"
#include "ProjectileFactory.h"
#include "Projectile.h"
#include "Artifact.h"

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
  virtual void update ();

  /**
   * @copydoc Character::draw(float interpolation, float scaleX, float scaleY, float rotation)
   */
  virtual void draw(float interpolation, float scaleX = 1, float scaleY = 1, float rotation = 0);
  
  /**
  * getHealthPercent
  *
  * Gets the player's current health as a percentage.
  * Used for generating the health bar.
  * @return double - percentage of health remaining
  */
  double getHealthPercent ();

  /**
  * getManaPercent
  *
  * Gets the player's current mana as a percentage.
  * Used for generating the mana bar.
  * @return double - percentage of mana remaining
  */
  double getManaPercent ();

  /**
  * getArtifactCount
  *
  * Returns the number of artifacts the player has.
  * @return int - the number of artifacts obtained.
  */
  int getArtifactCount ();

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
  void initAnimations();
  void handleKeyboard();
  void addSounds();
  Projectile* generateFireball( bool facingLeft );
  void handleMovements();
  void handleAttacks();

  int maxHealth, mana, maxMana;
  bool jumping, falling, punching, kicking, casting;
  bool hasJumped;
  bool hasDoubleJumped;
  bool facingLeft;
  TGA::BoundingBox subBounds[4];
  std::string currAnimationName;
  std::vector<Artifact*> artifacts;
};

