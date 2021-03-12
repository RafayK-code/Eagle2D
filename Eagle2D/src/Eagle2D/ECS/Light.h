#pragma once
#include "ECS.h"
#include "Mathematics.h"
#include <string>

namespace Eagle
{
	//Pre defined component
	//Used to attach lighting to an entity
	struct EAGLE_API Light : public ECS::Component
	{
		Light(std::string id, float radius, Vector2f center)
			: id(id), radius(radius), center(center)
		{
			tint.r = 255;
			tint.g = 255;
			tint.b = 255;
			tint.a = 255;
		}

		Light(std::string id, float radius, Vector2f center, SDL_Color tint)
			: id(id), radius(radius), center(center), tint(tint)
		{
		}

		std::string id;
		float radius;

		Vector2f center;
		SDL_Color tint;
	};
}