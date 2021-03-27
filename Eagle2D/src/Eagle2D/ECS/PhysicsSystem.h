#pragma once
#include "ECS.h"
#include "Graphics/Window.h"

namespace Eagle
{
	//Pre defined system
	//Runs through all entities with a transform and rigidbody component
	//Checks for collision, controlls velocity and acceleration;
	class EAGLE_API PhysicsSystem : public ECS::System
	{
	public:
		PhysicsSystem(ECS::Manager* manager);
		~PhysicsSystem();

		void Init(Window* window);

		void Update();

	private:
		ECS::Manager* _Manager;
		Window* _Window;
	};
}