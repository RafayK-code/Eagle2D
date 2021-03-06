#pragma once
#include "ECS.h"
#include "Mathematics.h"
#include <vector>

namespace Eagle
{
	//Pre defined component
	//Holds a Rectangle which represents the hitbox of the entity
	//Rectangle is in relation to the entity's position (if entity is at 400 x, 200 y, and is 64 by 64, passing in 0, 0, 64, 64 means that the hitbox will cover the entire player)
	//Holds a velocity vector and an acceleration vector
	struct RigidBody : public ECS::Component
	{
		RigidBody(Rect hitbox)
			: hitbox(hitbox), velocity(), acceleration()
		{
		}

		RigidBody(Rect hitbox, Eagle::Vector2f vel, Eagle::Vector2f acceleration)
			: hitbox(hitbox), velocity(vel), acceleration(acceleration)
		{
		}

		Eagle::Rect hitbox;

		Eagle::Vector2f velocity;
		Eagle::Vector2f acceleration;
	};
}