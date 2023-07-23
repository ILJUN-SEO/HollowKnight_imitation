#pragma once
#include <cmath>


namespace IJ::Math
{
	struct Vector2
	{
		Vector2()
			: x(0.0f)
			, y(0.0f)
		{}

		Vector2(float x_input, float y_input)
			: x(x_input)
			, y(y_input)
		{}

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		float x;
		float y;

		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 normalize()
		{
			float len = length();
			x /= len;
			y /= len;

			return *this;
		}

		Vector2 operator -()
		{
			return Vector2(-x, -y);
		}

		Vector2 operator+(const Vector2 other)
		{
			Vector2 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;

			return temp;
		}

		Vector2 operator-(const Vector2 other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;

			return temp;
		}

		Vector2 operator*(const float value)
		{
			Vector2 temp;
			temp.x = x * value;
			temp.y = y * value;

			return temp;
		}

		Vector2 operator/(const float value)
		{
			Vector2 temp;
			temp.x = x / value;
			temp.y = y / value;

			return temp;
		}

		Vector2& operator +=(const Vector2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vector2& operator -=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		bool operator ==(const Vector2& other)
		{
			return (x == other.x && y == other.y);
		}
	};
}