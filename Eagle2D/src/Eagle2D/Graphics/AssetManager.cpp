#include "egpch.h"
#include "AssetManager.h"
#include "Window.h"
#include <SDL_image.h>
#include "ECS/ECS.h"

#include "ECS/Sprite.h"
#include "ECS/Transform.h"

namespace Eagle
{
	AssetManager::AssetManager()
		: _Window(nullptr)
	{
	}

	AssetManager::~AssetManager()
	{
		for (auto const& pair : _Textures)
		{
			SDL_DestroyTexture(pair.second);
		}

		for (auto const& pair : _Fonts)
		{
			TTF_CloseFont(pair.second);
		}

		EG_CORE_WARN("Asset Manager destroyed.");
	}

	void AssetManager::Init(Window* window)
	{
		_Window = window;
		EG_CORE_INFO("Asset Manager initialized.");
	}

	void AssetManager::AddTexture(const char* file, std::string name)
	{
		SDL_Surface* temp = IMG_Load(file);

		if (temp == nullptr)
		{
			EG_CORE_WARN(file, " was not found. Image could not be loaded.");
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(_Window->_Renderer, temp);
		_Textures.insert({ name, tex });

		SDL_FreeSurface(temp);
	}

	void AssetManager::DeleteTexture(std::string name)
	{
		SDL_Texture* tex = _Textures[name];
		_Textures.erase(name);
		SDL_DestroyTexture(tex);
	}

	void AssetManager::DrawTexture(std::string name, SDL_Rect* src, SDL_Rect* dst, float angle, SDL_Point* point, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(_Window->_Renderer, _Textures[name], src, dst, angle, point, flip);
	}

	SDL_Texture* AssetManager::GetTexture(std::string name)
	{
		return _Textures[name];
	}

	void AssetManager::AddFont(const char* file, std::string name, int fontSize)
	{
		TTF_Font* font = TTF_OpenFont(file, fontSize);

		if (font == nullptr)
		{
			EG_CORE_WARN(file, " was not found. TTF could not be loaded.");
		}

		_Fonts.insert({ name, font });
	}

	void AssetManager::DeleteFont(std::string name)
	{
		TTF_Font* font = _Fonts[name];
		_Fonts.erase(name);
		TTF_CloseFont(font);
	}

	TTF_Font* AssetManager::GetFont(std::string name)
	{
		return _Fonts[name];
	}

	void AssetManager::AddBlankTexture(std::string name)
	{
		SDL_Texture* blankTex = SDL_CreateTexture(_Window->_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);

		if (blankTex == nullptr)
		{
			EG_CORE_ERROR("Blank texture could not be created for an unknown reason.");
		}

		_Textures.insert({ name, blankTex });
	}
}