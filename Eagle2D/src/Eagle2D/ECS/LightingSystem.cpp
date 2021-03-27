#include "egpch.h"
#include "LightingSystem.h"

#include <SDL.h>
#include "Light.h"
#include "Transform.h"

namespace Eagle
{
	LightingSystem::LightingSystem(ECS::Manager* man)
		: _Manager(man), _Window(nullptr), _aManager(nullptr)
	{
		EG_CORE_INFO("Lighting system created.");
	}

	LightingSystem::~LightingSystem()
	{
		EG_CORE_WARN("Lighting system destroyed.");
	}

	void LightingSystem::Init(Window* window, AssetManager* manager)
	{
		_aManager = manager;
		_Window = window;

		std::string blankTexture = "lightLayer";
		_aManager->AddBlankTexture(blankTexture);

		_TexLayer = blankTexture;

		for (const ECS::EntityID entity : _Entities)
		{
			Light& light = _Manager->GetComponent<Light>(entity);
			SDL_SetTextureBlendMode(_aManager->GetTexture("light"), SDL_BLENDMODE_ADD);
			break;
		}

		SDL_SetRenderDrawBlendMode(*_Window->GetRenderer(), SDL_BLENDMODE_BLEND);

		SDL_SetTextureBlendMode(_aManager->GetTexture(_TexLayer), SDL_BLENDMODE_MOD);
	}

	void LightingSystem::Update(SDL_Color brightness)
	{
		SDL_SetRenderTarget(_Window->_Renderer, _aManager->GetTexture(_TexLayer));
		SDL_SetRenderDrawColor(_Window->_Renderer, brightness.r, brightness.g, brightness.b, brightness.a);
		SDL_RenderClear(_Window->_Renderer);

		SDL_RenderFillRect(_Window->_Renderer, nullptr);

		for (const ECS::EntityID entity : _Entities)
		{
			Light& light = _Manager->GetComponent<Light>(entity);
			Transform& trans = _Manager->GetComponent<Transform>(entity);

			light.center = trans.transform.position + trans.transform.scale / 2.0f;

			SDL_SetTextureColorMod(_aManager->GetTexture(light.id), light.tint.r, light.tint.g, light.tint.b);

			SDL_Rect dst = { static_cast<int>(light.center.x - light.radius), static_cast<int>(light.center.y - light.radius), light.radius * 2, light.radius * 2 };

			SDL_RenderCopy(*_Window->GetRenderer(), _aManager->GetTexture(light.id), nullptr, &dst);
		}

		SDL_SetRenderTarget(_Window->_Renderer, nullptr);
		SDL_RenderClear(_Window->_Renderer);
	}

	void LightingSystem::Clear()
	{
		SDL_RenderCopy(_Window->_Renderer, _aManager->GetTexture(_TexLayer), nullptr, nullptr);
	}
}