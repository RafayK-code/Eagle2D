#include "egpch.h"
#include "AssetManager.h"
#include "Window.h"
#include <SDL_image.h>

namespace Eagle
{
	AssetManager::AssetManager()
	{
	}

	AssetManager::~AssetManager()
	{
		for (auto const& pair : m_Textures)
		{
			SDL_DestroyTexture(pair.second);
		}

		for (auto const& pair : m_Fonts)
		{
			TTF_CloseFont(pair.second);
		}

		EG_CORE_WARN("Asset Manager destroyed.");
	}

	void AssetManager::Init(Window* window)
	{
		m_Window = window;

		EG_CORE_INFO("Asset Manager initialized.");
	}

	void AssetManager::AddTexture(const char* file, std::string name)
	{
		SDL_Surface* temp = IMG_Load(file);

		if (temp == nullptr)
		{
			EG_CORE_WARN(file, " was not found. Image could not be loaded.");
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(m_Window->m_Renderer, temp);
		m_Textures.insert({ name, tex });

		SDL_FreeSurface(temp);
	}

	void AssetManager::DeleteTexture(std::string name)
	{
		SDL_Texture* tex = m_Textures[name];
		m_Textures.erase(name);
		SDL_DestroyTexture(tex);
	}

	void AssetManager::DrawTexture(std::string name, SDL_Rect* src, SDL_Rect* dst, float angle, SDL_Point* point, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(m_Window->m_Renderer, m_Textures[name], src, dst, angle, point, flip);
	}

	SDL_Texture* AssetManager::GetTexture(std::string name)
	{
		return m_Textures[name];
	}

	void AssetManager::AddFont(const char* file, std::string name, int fontSize)
	{
		TTF_Font* font = TTF_OpenFont(file, fontSize);

		if (font == nullptr)
		{
			EG_CORE_WARN(file, " was not found. TTF could not be loaded.");
		}

		m_Fonts.insert({ name, font });
	}

	void AssetManager::DeleteFont(std::string name)
	{
		TTF_Font* font = m_Fonts[name];
		m_Fonts.erase(name);
		TTF_CloseFont(font);
	}

	TTF_Font* AssetManager::GetFont(std::string name)
	{
		return m_Fonts[name];
	}

	void AssetManager::CreateLight(std::string name, SDL_Colour tint)
	{
		std::shared_ptr<Light> light = std::make_shared<Light>();
		light->CreateLight(*m_Window, tint);
		m_Lights.insert({ name, std::move(light) });
	}

	void AssetManager::DeleteLight(std::string name)
	{
		m_Lights.erase(name);
	}

	void AssetManager::DrawLight(std::string name, std::string texture, Vector2f origin, float radius)
	{
		SDL_SetRenderDrawColor(m_Window->m_Renderer, 0, 0, 0, 255);
		SDL_SetRenderTarget(m_Window->m_Renderer, m_Lights[name]->GetTexture());
		SDL_RenderClear(m_Window->m_Renderer);

		SDL_Rect dst = { origin.x - radius, origin.y - radius, radius * 2, radius * 2 };

		SDL_RenderCopy(m_Window->m_Renderer, GetTexture(texture), nullptr, &dst);
	}

	std::shared_ptr<Light> AssetManager::GetLight(std::string name)
	{
		return m_Lights[name];
	}
}