#pragma once

namespace Eagle
{
	struct Vector2f
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
		}
	};
}