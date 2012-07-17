#pragma once

#include <ProjIncludes.h>
#include <Texture.h>
#include <Animation.h>
#include <Vector2D.h>

namespace Sandstorms
{
	class Character
	{
	public:
		Character(std::string texName, int lvl, int xPos = 0, int yPos = 0);
		virtual ~Character();

		//virtual void moveToward(Character& who) = 0; PUT THIS IN ENEMY

		virtual void attack(Character& who) = 0;
		
		void takeDamage(int damage);
		int getHealth();
		TGA::Vector2D getPosition();
		SDL_Rect getBounds();

		void increaseAccels(float xAcceleration, float yAcceleration);
		
		virtual void updatePosition();

		bool isAlive();

		void draw();

	protected:
		virtual void initAttributes(int level) = 0;
		void setX(float xVal);
		void setY(float yVal);
		void setPosition(float xVal, float yVal);

		TGA::Texture texture;
		TGA::Animation animation;

		bool alive;

		int health, level, speed;
		int currentAttack;
		SDL_Rect bounds;

		TGA::Vector2D position, velocity, accel;
		
		//std::vector<Attack> attacks;
		//int currAttack;
	};
}

