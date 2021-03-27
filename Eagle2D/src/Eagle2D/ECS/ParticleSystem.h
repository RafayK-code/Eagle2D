#pragma once
#include "ECS.h"
#include "Core.h"
#include "Graphics/Window.h"

namespace Eagle
{
	class EAGLE_API ParticleSystem : public ECS::System
	{
	public:
		ParticleSystem(ECS::Manager* manager);
		~ParticleSystem();

		void Init(Window* window);

		void Update();

	private:
		ECS::Manager* _Manager;

		Window* _Window;
	};
}