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
		if (SDL_PollEvent(&event))
		{
			EventScript(event);
		}
	}
}