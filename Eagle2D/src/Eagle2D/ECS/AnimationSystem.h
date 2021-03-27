#pragma once
#include "ECS.h"

namespace Eagle
{
	//Pre defined system
	//Runs through all entities with an animation component
	//Animates them
	class EAGLE_API AnimationSystem : public ECS::System
	{
	public:
		AnimationSystem(ECS::Manager* manager);
		~AnimationSystem();

		void Init();

		void Update();

	private:
		ECS::Manager* _Manager;
	};
}