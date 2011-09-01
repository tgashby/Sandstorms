#pragma once

namespace TGA
{
	class Vector2D
	{
	public:
		Vector2D(float x, float y);
		~Vector2D(void);

		Vector2D operator+(Vector2D);
		Vector2D operator-(Vector2D);
		Vector2D scalarProduct(int);
		Vector2D normalize();

		float dotProduct(Vector2D);
		float length();
		float distanceFrom(Vector2D);

		float getX();
		float getY();

	private:
		float x, y;
	};
}
