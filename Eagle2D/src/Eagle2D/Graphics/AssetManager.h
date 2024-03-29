#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

#include "Window.h"

#include "ECS/ECS.h"

#pragma warning(push)
#pragma warning(disable:4251)

namespace Eagle
{
	class EAGLE_API AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		void Init(Window* window);

		void AddTexture(const char* file, std::string name);
		void DeleteTexture(std::string name);
		void DrawTexture(std::string name, SDL_Rect* src, SDL_Rect* dst, float angle, SDL_Point* point, SDL_RendererFlip flip);
		SDL_Texture* GetTexture(std::string name);
		
		void AddFont(const char* file, std::string name, int fontSize);
		void DeleteFont(std::string name);
		TTF_Font* GetFont(std::string name);

		void AddBlankTexture(std::string name);

	private:
		std::unordered_map<std::string, SDL_Texture*> _Textures;
		std::unordered_map<std::string, TTF_Font*> _Fonts;

		Window* _Window;
	};
}

#pragma warning(pop)