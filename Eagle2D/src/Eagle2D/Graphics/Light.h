#pragma once
#include "Core.h"
#include "Mathematics.h"
#include <unordered_set>

namespace Eagle
{
	class Window;

	class EAGLE_API Light
	{
	public:
		Light();
		~Light();

		void CreateLight(Window& window, SDL_Colour colour);
		void DestroyLight();

		SDL_Texture* GetTexture();

	private:
		Vector2f m_Position;
		int m_Brightness;

		SDL_Texture* m_RendLight;
	};
}