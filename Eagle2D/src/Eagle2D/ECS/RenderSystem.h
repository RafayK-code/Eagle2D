#pragma once
#include "ECS.h"
#include "Graphics/AssetManager.h"

namespace Eagle
{
	//Pre defined system
	//Renders all entities
	//Renders according to layer level
	class EAGLE_API RenderSystem : public ECS::System
	{
	public:
		RenderSystem(ECS::Manager* manager);
		~RenderSystem();

		void Init(AssetManager* assetManager);
		void Update();

		void UpdateLayers();

	private:
		ECS::Manager* m_Manager;

		AssetManager* m_aManager;
	};
}