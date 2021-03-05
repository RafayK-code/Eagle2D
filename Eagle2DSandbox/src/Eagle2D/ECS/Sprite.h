#pragma once
#include "ECS.h"
#include <SDL.h>
#include <string>

//Pre defined component.
//Holds a name associated with a texture in the AssetManager
//Holds the location of texture being used, size of the sprite (associats with Transform::position by default)
//Holds an enum of how the sprite should be flipped
struct Sprite : public Eagle::ECS::Component
{
	Sprite(std::string id, SDL_Rect src)
		: id(id), src(src)
	{
	}

	Sprite(std::string id, SDL_Rect src, SDL_RendererFlip flip)
		: id(id), src(src), flip(flip)
	{
	}

	std::string id;

	SDL_Rect src;
	SDL_Rect dst;

	SDL_RendererFlip flip;
};