#pragma once
#include "ECS.h"
#include "Mathematics.h"

//Pre defined component
//Holds a Rectangle which holds a position in 2D space and a width and height;
struct Transform : public Eagle::ECS::Component
{
	Transform(Eagle::Rect transform, float rotation)
		: transform(transform), rotation(rotation)
	{
	}

	Eagle::Rect transform;

	float rotation;
};