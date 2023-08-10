#pragma once
#include <cmath>


namespace IJ::Math
{
#define PI 3.141592f

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
		Vector2 operator*(const Vector2 other)
		{
			Vector2 temp;
			temp.x = x * other.x;
			temp.y = y * other.y;

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

		Vector2& operator *=(const float value)
		{
			x *= value;
			y *= value;

			return *this;
		}

		//Vector2& operator *=(const Vector2& other)
		//{
		//	x *= other.x;
		//	y *= other.y;

		//	return *this;
		//}

		Vector2& operator /=(const Vector2& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		bool operator ==(const Vector2& other)
		{
			return (x == other.x && y == other.y);
		}
	};

	inline Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.normalize();
		float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
		float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

		return Vector2(x, y);
	}

	inline float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline float Cross(Vector2 v1, Vector2 v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
}