#pragma once
#include "ECS.h"
#include "Mathematics.h"
#include <vector>

//Pre defined component
//Holds a polygon 
struct RigidBody : public Eagle::ECS::Component
{
	RigidBody(Eagle::Rect hitbox, Eagle::Vector2f vel, Eagle::Vector2f acceleration)
		: hitbox(hitbox), velocity(vel), acceleration(acceleration)
	{
	}

	Eagle::Rect hitbox;

	Eagle::Vector2f velocity;
	Eagle::Vector2f acceleration;
};