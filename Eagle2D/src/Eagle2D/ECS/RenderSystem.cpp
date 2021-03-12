#include "egpch.h"
#include "RenderSystem.h"

#include "Transform.h"
#include "Sprite.h"

namespace Eagle
{
	RenderSystem::RenderSystem(ECS::Manager* man)
		: m_Manager(man)
	{
		EG_CORE_INFO("Render system created.");
	}

	RenderSystem::~RenderSystem()
	{
		EG_CORE_WARN("Render system destroyed.");
	}

	void RenderSystem::Init(AssetManager* aManager)
	{
		m_aManager = aManager;
	}

	void RenderSystem::UpdateLayers()
	{
		m_aManager->UpdateLayers(m_Entities, *m_Manager);
	}

	void RenderSystem::Update()
	{
		for (const ECS::EntityID entity : m_Entities)
		{
			Sprite& sprite = m_Manager->GetComponent<Sprite>(entity);
			Transform& transform = m_Manager->GetComponent<Transform>(entity);

			sprite.dst.x = static_cast<int>(transform.transform.position.x);
			sprite.dst.y = static_cast<int>(transform.transform.position.y);
			sprite.dst.w = static_cast<int>(transform.transform.scale.x);
			sprite.dst.h = static_cast<int>(transform.transform.scale.y);

			SDL_Point point;
			point.x = static_cast<int>(transform.origin.x);
			point.y = static_cast<int>(transform.origin.y);

			m_aManager->DrawTexture(sprite.id, &sprite.src, &sprite.dst, transform.rotation, &point, sprite.flip);
		}
	}
}