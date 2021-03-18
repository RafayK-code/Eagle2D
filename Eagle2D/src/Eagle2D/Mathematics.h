#pragma once
#include <Core.h>
#include <vector>
#include <cmath>

constexpr double pi = 3.14159265358979323846;

namespace Eagle
{
	struct EAGLE_API Vector2f
	{
		float x, y;

		Vector2f()
			: x(0.0f), y(0.0f)
		{
		}

		Vector2f(float x, float y)
			: x(x), y(y)
		{
		}

		Vector2f(Vector2f const& vec)
			: x(vec.x), y(vec.y)
		{
		}

		Vector2f operator+(Vector2f const& vec)
		{
			return Vector2f(x + vec.x, y + vec.y);
		}

		Vector2f operator-(Vector2f const& vec)
		{
			return Vector2f(x - vec.x, y - vec.y);
		}

		Vector2f operator/(float sc)
		{
			return Vector2f(x / sc, y / sc);
		}

		Vector2f operator*(float sc)
		{
			return Vector2f(x * sc, y * sc);
		}

		Vector2f& operator+=(Vector2f const& vec)
		{
			this->x += vec.x;
			this->y += vec.y;

			return *this;
		}

		Vector2f& operator-=(Vector2f const& vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;

			return *this;
		}

		Vector2f& operator*=(float sc)
		{
			this->x *= sc;
			this->y *= sc;

			return *this;
		}

		Vector2f& operator/=(float sc)
		{
			this->x /= sc;
			this->y /= sc;

			return *this;
		}

		bool operator!=(Vector2f const& vec)
		{
			if (this->x != vec.x || this->y != vec.y)
			{
				return true;
			}

			return false;
		}

		bool operator==(Vector2f const& vec)
		{
			if (this->x == vec.x && this->y == vec.y)
			{
				return true;
			}

			return false;
		}

		void Zero()
		{
			x = 0.0f;
			y = 0.0f;
		}
	};

	struct EAGLE_API Rect
	{
		Vector2f position;
		Vector2f scale;

		Rect()
			: position(0.0f, 0.0f), scale(0.0f, 0.0f)
		{
		}

		Rect(float x, float y, float w, float h)
			: position(x, y), scale(w, h)
		{
		}

		Rect(Vector2f const& position, Vector2f const& scale)
			: position(position), scale(scale)
		{
		}

		Rect(Rect const& rect)
			: position(rect.position.x, rect.position.y), scale(rect.scale.x, rect.scale.y)
		{
		}

		//operator to detect collision between two Rects
		bool operator>>(Rect const& rect)
		{
			if (
				this->position.x + this->scale.x >= rect.position.x  &&
				rect.position.x + rect.scale.x   >= this->position.x &&
				this->position.y + this->scale.y >= rect.position.y  &&
				rect.position.y + rect.scale.y   >= this->position.y
				)
			{
				return true;
			}

			return false;
		}
	};
}