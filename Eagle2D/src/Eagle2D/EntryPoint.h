#pragma once

#ifdef EAGLE_PLATFORM_WINDOWS

extern Eagle::Application* Eagle::CreateApplication();

int main(int agrc, char** argv)
{
	auto app = Eagle::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif