#pragma once
#include "Core.h"
#include "ECS.h"
#include <SDL.h>
#include <string>

namespace Eagle
{
	//Pre defined component.
	//Holds a name associated with a texture in the AssetManager
	//Holds the location of texture being used, size of the sprite (associats with Transform::position by default)
	//Holds an enum of how the sprite should be flipped
	struct EAGLE_API Sprite : public ECS::Component
	{
		Sprite(std::string id, std::uint8_t layer)
			:id(id), layer(layer), src(SDL_Rect{ 0, 0, 0, 0 }), flip(SDL_FLIP_NONE), dst(SDL_Rect{ 0, 0, 0, 0 })
		{
		}

		Sprite(std::string id, std::uint8_t layer, SDL_Rect src)
			: id(id), layer(layer), src(src), flip(SDL_FLIP_NONE), dst(SDL_Rect{ 0, 0, 0, 0 })
		{
		}

		Sprite(std::string id, std::uint8_t layer, SDL_Rect src, SDL_RendererFlip flip)
			: id(id), layer(layer), src(src), flip(flip), dst(SDL_Rect{ 0,0,0,0 })
		{
		}

		Sprite(std::string id, std::uint8_t layer, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
			: id(id), layer(layer), src(src), dst(dst), flip(flip)
		{
		}

		std::string id;

		SDL_Rect src;
		SDL_Rect dst;

		SDL_RendererFlip flip;

		std::uint8_t layer;
	};
}