#include "egpch.h"
#include "EventHandler.h"
#include "Graphics/Window.h"

namespace Eagle
{
	EventHandler::EventHandler()
	{
	}

	EventHandler::~EventHandler()
	{
	}

	void EventHandler::HandleEvents(Window* window)
	{
		SDL_Event event;
		Uint32 timeout = SDL_GetTicks() + 10;
		while (SDL_PollEvent(&event) && !SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
		{
			//EventScript(event);
		}
	}
}