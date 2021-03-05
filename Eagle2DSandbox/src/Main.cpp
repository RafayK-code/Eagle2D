#include <iostream>
#include <SDL.h>
#include "Eagle2D/Graphics/Window.h"
#include "EventHandler.h"

Eagle::Window window;

void Eagle::EventHandler::CustomEvents(SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		window.Close();
	}

	switch (event.key.keysym.sym)
	{
	case SDLK_RETURN:
		std::cout << "Enter Key Pressed" << std::endl;
		break;
	}
}

int main(int agrc, char** argv)
{
	window.Init("App", 1280, 720, SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);
	window.SetFrameRate(240);

	Eagle::EventHandler handler;

	while (window.IsOpen())
	{
		handler.HandleEvents(&window);

		window.Clear();
		//Drawing goes here.
		window.Update();
	}

	return 0;
}