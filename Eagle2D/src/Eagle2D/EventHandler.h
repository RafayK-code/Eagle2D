#pragma once
#include <SDL.h>
#include <vector>
#include <memory>

namespace Eagle
{
	class Window;

	class EAGLE_API EventHandler
	{
	public:
		EventHandler();
		~EventHandler();

		void HandleEvents(Window* window);

		//Defined in client
		void EventScript(SDL_Event event);
	};
}