#pragma once
#include "ECS.h"
#include "Graphics/AssetManager.h"

namespace Eagle
{
	class EAGLE_API LightingSystem : public ECS::System
	{
	public:
		LightingSystem(ECS::Manager* manager);
		~LightingSystem();

		void Init(Window* window, AssetManager* assetManager);

		void Update(SDL_Color brightness);
		void Clear();

	private:
		ECS::Manager* m_Manager;
		AssetManager* m_aManager;
		Window* m_Window;

		std::string texLayer;
	};
}