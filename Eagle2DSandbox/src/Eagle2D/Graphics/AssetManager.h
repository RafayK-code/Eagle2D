#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>

namespace Eagle
{
	struct Animation
	{

	};

	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		void AddTexture(const char* file, std::string name);
		void DeleteTexture(std::string name);
		void DrawTexture(std::string name, SDL_Rect* src, SDL_Rect* dst, float angle, SDL_Point* point, SDL_RendererFlip flip);
		SDL_Texture* GetTexture(std::string name);
		
		void AddFont(const char* file, std::string name, int fontSize);
		void DeleteFont(std::string name);
		TTF_Font* GetFont(std::string name);

	private:
		std::unordered_map<std::string, SDL_Texture*> m_Textures;
		std::unordered_map<std::string, TTF_Font*> m_Fonts;
	};
}