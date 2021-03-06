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
	}

	void AssetManager::AddTexture(const char* file, std::string name)
	{
		SDL_Surface* temp = IMG_Load(file);

		if (temp == nullptr)
		{
			EG_WARN(file, " was not found. Error : Image could not be loaded.");
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::m_Renderer, temp);
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
		SDL_RenderCopyEx(Window::m_Renderer, m_Textures[name], src, dst, angle, point, flip);
	}

	SDL_Texture* AssetManager::GetTexture(std::string name)
	{
		return m_Textures[name];
	}

	void AssetManager::AddFont(const char* file, std::string name, int fontSize)
	{
		TTF_Font* font = TTF_OpenFont(file, fontSize);
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
}