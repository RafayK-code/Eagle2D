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
		std::unordered_map<ECS::EntityID, std::uint8_t> entities;
		std::vector<std::pair<ECS::EntityID, std::uint8_t>> A;

		for (const ECS::EntityID entity : m_Entities)
		{
			Sprite& sprite = m_Manager->GetComponent<Sprite>(entity);
			A.push_back(std::pair<ECS::EntityID, std::uint8_t>({ entity, sprite.layer }));
		}

		std::sort(A.begin(), A.end(), Compare<ECS::EntityID, std::uint8_t>);

		m_Entities.clear();
		for (const auto& pair : A)
		{
			m_Entities.insert(pair.first);
		}
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

			if (!(sprite.src.x == 0 && sprite.src.y == 0 && sprite.src.w == 0 && sprite.src.h == 0))
			{
				m_aManager->DrawTexture(sprite.id, &sprite.src, &sprite.dst, transform.rotation, &point, sprite.flip);
			}

			else
			{
				m_aManager->DrawTexture(sprite.id, nullptr, &sprite.dst, transform.rotation, &point, sprite.flip);
			}
		}
	}
}