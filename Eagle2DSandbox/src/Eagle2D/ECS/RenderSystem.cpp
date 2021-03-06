#include "egpch.h"
#include "RenderSystem.h"
#include <SDL.h>
#include "Graphics/AssetManager.h"

#include "Sprite.h"
#include "Transform.h"
#include "Graphics/Window.h"

namespace Eagle
{
	RenderSystem::RenderSystem(ECS::Manager* man)
		: manager(man)
	{
	}

	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::Init(AssetManager* aMan)
	{
		aManager = aMan;
	}

	void RenderSystem::Update()
	{
		for (const ECS::EntityID entity : m_Entities)
		{
			Sprite& sprite = manager->GetComponent<Sprite>(entity);
			Transform& transform = manager->GetComponent<Transform>(entity);

			sprite.dst.x = static_cast<int>(transform.transform.position.x);
			sprite.dst.y = static_cast<int>(transform.transform.position.y);
			sprite.dst.w = static_cast<int>(transform.transform.scale.x);
			sprite.dst.h = static_cast<int>(transform.transform.scale.y);

			SDL_Point point;
			point.x = static_cast<int>(transform.origin.x);
			point.y = static_cast<int>(transform.origin.y);

			aManager->DrawTexture(sprite.id, &sprite.src, &sprite.dst, transform.rotation, &point, sprite.flip);
		}
	}
}