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
		EventHandler() {}
		~EventHandler() {}

		void HandleEvents(void(*event_script)(SDL_Event))
		{
			SDL_Event event;
			Uint32 timeout = SDL_GetTicks() + 10;
			while (SDL_PollEvent(&event) && !SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
			{
				event_script(event);
			}
		}
	};
}