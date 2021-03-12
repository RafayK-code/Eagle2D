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

	void AssetManager::SetLayer(std::string texture, std::uint8_t layer)
	{
		m_Layers.insert({ layer, texture });
	}

	void AssetManager::UpdateLayers(std::unordered_set<ECS::EntityID>& entities, ECS::Manager& man)
	{
		std::unordered_set<ECS::EntityID> set;

		for (auto const& layer : m_Layers)
		{
			for (const ECS::EntityID entity : entities)
			{
				Sprite& sprite = man.GetComponent<Sprite>(entity);

				if (sprite.id == layer.second)
				{
					set.insert(entity);
				}
			}
		}

		entities = set;
	}

	void AssetManager::Update()
	{
	}

	void AssetManager::AddTexture(const char* file, std::string name)
	{
		SDL_Surface* temp = IMG_Load(file);

		if (temp == nullptr)
		{
			EG_CORE_WARN(file, " was not found. Image could not be loaded.");
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(*m_Window->GetRenderer(), temp);
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
		SDL_RenderCopyEx(*m_Window->GetRenderer(), m_Textures[name], src, dst, angle, point, flip);
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

	void AssetManager::AddBlankTexture(std::string name)
	{
		SDL_Texture* blankTex = SDL_CreateTexture(*m_Window->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);

		if (blankTex == nullptr)
		{
			EG_CORE_ERROR("Blank texture could not be created for an unknown reason.");
		}

		m_Textures.insert({ name, blankTex });
	}
}