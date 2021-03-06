#pragma once
#include "ECS.h"

namespace Eagle
{
	//Pre defined system
	//Runs through all entities with a transform and rigidbody component
	//Checks for collision, controlls velocity and acceleration;
	class PhysicsSystem : public ECS::System
	{
	public:
		PhysicsSystem(ECS::Manager* manager);
		~PhysicsSystem();

		void Init();

		void Update();

	private:
		ECS::Manager* m_Manager;
	};
}