#pragma once
#include <SDL.h>
#include <vector>
#include <memory>

namespace Eagle
{
	class Window;

	class EventHandler
	{
	public:
		EventHandler();
		~EventHandler();

		void HandleEvents(Window* window);
		void CustomEvents(SDL_Event event);
		void CustomEvents(SDL_Event event, Window* window);
	};
}