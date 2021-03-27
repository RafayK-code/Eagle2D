#pragma once
#include "Core.h"
#include "ECS.h"
#include "Mathematics.h"

namespace Eagle
{
	struct EAGLE_API Particle : public ECS::Component
	{
		Particle(Vector2f vel, Vector2f acc, SDL_Color color, Uint32 lifeTime)
			: velocity(vel), acceleration(acc), color(color), lifeTime(lifeTime)
		{
		}

		Vector2f velocity;
		Vector2f acceleration;

		SDL_Color color;
		Uint32 lifeTime;
	};
}