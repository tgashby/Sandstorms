/**
 * @file Character.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <Collidable.h>
#include <Vector2D.h>
#include <Animation.h>
#include <map>
#include <string>


/**
 * @class Character
 *
 * @brief Base class for all "characters", the player and enemies.
 *
 */
class Character : public TGA::Collidable 
{
public:
  /**
  * Character
  *
  * Initializes the basic attributes of a Character.
  * @param int health - the health of the character
  * @param TGA::Vector2D position - the position of the character
  * @param TGA::Vector2D velocity - the velocity of the character
  */
  Character (int health = 100, TGA::Vector2D position = TGA::Vector2D(0,0), TGA::Vector2D velocity = TGA::Vector2D(0,0));

  ~Character ();

  /**
  * update
  *
  * Updates the character, handling position changes and
  * checking collisions as well as anything else desired.
  */
  virtual void update ();

  /**
  * draw
  *
  * Draw the character using its current Animation.
  */
  virtual void draw ();

  /**
  * getPosition
  *
  * Gets the character's current position.
  * @return TGA::Vector2D - the current position
  */
  TGA::Vector2D getPosition ();

  /**
  * isAlive
  *
  * Determines whether or not this character is still alive.
  * @return bool - true if the character is alive
  */
  bool isAlive ();

  /**
   * handleCollision
   *
   * Update the state of the characters based on what it collided with.
   * @param TGA::Collidable collidedWith - the entity collided with
   * @return void -
   */
  virtual void handleCollision (TGA::Collidable collidedWith);

protected:
  int health;
  TGA::Vector2D position;
  TGA::Vector2D velocity;
  std::map<std::string, TGA::Animation> animations;
  TGA::Animation currAnimation;
  bool alive;
};

