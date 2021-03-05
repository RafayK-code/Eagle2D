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
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_f:
					window->FullScreen(true);
					break;
				case SDLK_g:
					window->FullScreen(false);
					break;
				}
				break;
			}
			CustomEvents(event);
		}
	}
}