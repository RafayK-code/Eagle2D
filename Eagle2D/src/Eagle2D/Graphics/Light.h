#pragma once
#include "Core.h"
#include "Mathematics.h"
#include "Window.h"

namespace Eagle
{
	class EAGLE_API Light
	{
	public:
		Light();
		~Light();

		void Init(SDL_Texture* shadowTexture, SDL_Colour shadowColour)

		void CreateLight(Window* window, Vector2f position, int brightness);
		void DestroyLight();

	private:
		Vector2f m_Position;
		int m_Brightness;

		Window* window;
	};
}