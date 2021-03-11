#include "egpch.h"
#include "Light.h"
#include "ECS/ECS.h"
#include "Window.h"
#include "AssetManager.h"

namespace Eagle
{
	Light::Light()
	{
	}

	Light::~Light()
	{
	}

	void Light::CreateLight(Window& window, SDL_Colour colour)
	{
		m_RendLight = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
		SDL_SetTextureBlendMode(m_RendLight, SDL_BLENDMODE_MOD);
		SDL_SetTextureColorMod(m_RendLight, colour.r, colour.g, colour.b);
	}

	void Light::DestroyLight()
	{
		SDL_DestroyTexture(m_RendLight);
	}

	SDL_Texture* Light::GetTexture()
	{
		return m_RendLight;
	}
}