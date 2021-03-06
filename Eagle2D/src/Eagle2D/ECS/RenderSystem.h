#pragma once
#include "ECS.h"

namespace Eagle
{
	class AssetManager;
	//Pre defined system
	//Runs through all entities that have a sprite and transform component
	//Updates their destination rectangle and draws it onto the screen;
	class EAGLE_API RenderSystem : public ECS::System
	{
	public:
		RenderSystem(ECS::Manager* manager);
		~RenderSystem();

		void Init(AssetManager* aManager);

		void Update();

	private:
		ECS::Manager* m_Manager;
		AssetManager* m_aManager;
	};
}