#include "egpch.h"
#include "LightingSystem.h"

#include <SDL.h>
#include "Light.h"
#include "Transform.h"

namespace Eagle
{
	LightingSystem::LightingSystem(ECS::Manager* man)
		: m_Manager(man)
	{
		EG_CORE_INFO("Lighting system created.");
	}

	LightingSystem::~LightingSystem()
	{
		EG_CORE_WARN("Lighting system destroyed.");
	}

	void LightingSystem::Init(Window* window, AssetManager* manager)
	{
		m_aManager = manager;
		m_Window = window;

		std::string blankTexture = "lightLayer";
		m_aManager->AddBlankTexture(blankTexture);

		texLayer = blankTexture;

		for (const ECS::EntityID entity : m_Entities)
		{
			Light& light = m_Manager->GetComponent<Light>(entity);
			SDL_SetTextureBlendMode(m_aManager->GetTexture("light"), SDL_BLENDMODE_ADD);
			break;
		}

		SDL_SetRenderDrawBlendMode(*m_Window->GetRenderer(), SDL_BLENDMODE_BLEND);

		SDL_SetTextureBlendMode(m_aManager->GetTexture(texLayer), SDL_BLENDMODE_MOD);
	}

	void LightingSystem::Update(SDL_Color brightness)
	{
		SDL_SetRenderTarget(*m_Window->GetRenderer(), m_aManager->GetTexture(texLayer));
		SDL_SetRenderDrawColor(*m_Window->GetRenderer(), brightness.r, brightness.g, brightness.b, brightness.a);
		SDL_RenderClear(*m_Window->GetRenderer());

		SDL_RenderFillRect(*m_Window->GetRenderer(), nullptr);

		for (const ECS::EntityID entity : m_Entities)
		{
			Light& light = m_Manager->GetComponent<Light>(entity);
			Transform& trans = m_Manager->GetComponent<Transform>(entity);

			light.center = trans.transform.position + trans.transform.scale / 2.0f;

			SDL_SetTextureColorMod(m_aManager->GetTexture(light.id), light.tint.r, light.tint.g, light.tint.b);

			SDL_Rect dst = { static_cast<int>(light.center.x - light.radius), static_cast<int>(light.center.y - light.radius), light.radius * 2, light.radius * 2 };

			SDL_RenderCopy(*m_Window->GetRenderer(), m_aManager->GetTexture(light.id), nullptr, &dst);
		}

		SDL_SetRenderTarget(*m_Window->GetRenderer(), nullptr);
		SDL_RenderClear(*m_Window->GetRenderer());
	}

	void LightingSystem::Clear()
	{
		SDL_RenderCopy(*m_Window->GetRenderer(), m_aManager->GetTexture(texLayer), nullptr, nullptr);
	}
}