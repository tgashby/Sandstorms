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
#include <Engine.h>
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
  Character (int health = 100, TGA::Vector2D position = TGA::Vector2D(0,0), 
     TGA::Vector2D velocity = TGA::Vector2D(0,0), TGA::Vector2D acceleration = TGA::Vector2D(0, 1));

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
  * @param float interpolation - percentage between update frames
  * @param scaleX - a scale factor in X
  * @param scaleY - a scale factor in Y
  * @param rotation - a rotation, in degrees
  */
  virtual void draw (float interpolation, float scaleX = 1, float scaleY = 1, float rotation = 0);

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
  virtual void handleCollision (TGA::Collidable& collidedWith) = 0;

protected:
  int health;
  TGA::Vector2D position, velocity, acceleration;
  std::map<std::string, TGA::Animation*> animations;
  TGA::Animation* currAnimation;
  std::string currAnimationName;
  bool alive, facingLeft;
};

