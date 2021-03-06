#pragma once
#include <SDL.h>
#include <vector>
#include <memory>

extern void Eagle::EventScript(SDL_Event event);

namespace Eagle
{
	class Window;

	class EventHandler
	{
	public:
		EventHandler() {}
		~EventHandler() {}

		void HandleEvents()
		{
			SDL_Event event;
			Uint32 timeout = SDL_GetTicks() + 10;
			while (SDL_PollEvent(&event) && !SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
			{
				EventScript(event);
			}
		}
	};
}