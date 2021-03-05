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

		//Defined in client
		void EventScript(SDL_Event event);
	};
}