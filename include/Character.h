#pragma once

#include <ProjIncludes.h>
#include <Texture.h>
#include <Animation.h>

namespace Sandstorms
{
	class Character
	{
	public:
		Character(std::string texName, int lvl, int xPos = 0, int yPos = 0);
		virtual ~Character();

		virtual void moveToward(Character& who) = 0;
		virtual void attack(Character& who) = 0;
		
		void takeDamage(int damage);
		int getHealth();
		SDL_Point getPosition();
		SDL_Rect getBounds();

	protected:
		virtual void initAttributes(int level) = 0;
		void setX(int xVal);
		void setY(int yVal);
		void setPosition(SDL_Point newCoords);

		TGA::Texture texture;
		TGA::Animation animation;

		int health, level, speed;
		SDL_Point coords;
		SDL_Rect bounds;

		float xVel, yVel; 
		float xAccel, yAccel;
		
		//std::vector<Attack> attacks;
	};
}

