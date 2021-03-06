#pragma once
#include "Core.h"
#include "ECS.h"
#include "Mathematics.h"

namespace Eagle
{
	//Pre defined component
	//Holds a Rectangle which holds a position in 2D space and a width and height;
	//Holds a point which represents the origin of the entity
	//Holds a value in radians which represents the rotation around the origin
	struct EAGLE_API Transform : public ECS::Component
	{
		Transform(Rect transform, float rotation)
			: transform(transform), rotation(rotation)
		{
			origin.x = transform.position.x + transform.scale.x / 2.0f;
			origin.y = transform.position.y + transform.scale.y / 2.0f;
		}

		Transform(Rect transform, float rotation, Vector2f origin)
			: transform(transform), rotation(rotation), origin(origin)
		{
		}

		Rect transform;
		Vector2f origin;

		float rotation;
	};
}