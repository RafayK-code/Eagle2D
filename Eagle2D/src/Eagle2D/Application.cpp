#include "EaglePCH.h"
#include "Application.h"

#include "Graphics/RenderWindow.h"

namespace Eagle
{
	RenderWindow* window;

	Application::Application()
	{
		window = new RenderWindow();
		window->Init(WindowProps("Eagle2D", 1280, 720));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		window->OnUpdate();
	}
}