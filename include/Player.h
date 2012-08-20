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

class Projectile;
class Platform;
class Artifact;

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
   
   void addHealth(int howMuch);
   
   void addMana(int howMuch);
   
   /**
    * handleCollision
    *
    * Update the state of the Player based on what it collided with.
    * @param TGA::Collidable collidedWith - the entity collided with
    */
   virtual void handleCollision (TGA::Collidable& collidedWith);
   
private:
   void jump ();
   void initAnimations();
   void handleKeyboard();
   void addSounds();
   Projectile* generateFireball(bool facingLeft);
   void handleMovements();
   void handleAttacks();
   void punchAttack();
   void kickAttack();
   
   int maxHealth, mana, maxMana;
   bool jumping, falling, punching, kicking, casting, hurting;
   bool hasJumped, hasDoubleJumped, kickPlaying, castPlaying, canBeHurt;
   int artifactCount;
};

