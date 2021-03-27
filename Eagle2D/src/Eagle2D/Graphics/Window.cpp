#include "egpch.h"
#include "Window.h"
#include <SDL_image.h>

namespace Eagle
{
	Window::Window()
	{
	}

	Window::Window(const char* title, unsigned int width, unsigned int height, Uint32 windowFlags, Uint32 rendererFlags)
	{
		Init(title, width, height, windowFlags, rendererFlags);
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(_Renderer);
		SDL_DestroyWindow(_Window);
		SDL_Quit();

		EG_CORE_WARN("Window and Renderer Destroyed.");
		EG_CORE_TRACE("Thank you for using Eagle2D. Goodbye!");
	}

	void Window::Init(const char* title, unsigned int width, unsigned int height, Uint32 windowFlags, Uint32 rendererFlags)
	{
		_FrameRate = 0; _VSync = false; _FrameStart = SDL_GetTicks();

		EG_CORE_ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) + 1, "Could not initialize SDL.");

		EG_CORE_INFO("SDL initialized...");

		EG_CORE_ASSERT(IMG_Init(IMG_INIT_PNG), "Coult not initialize SDL_image.");

		EG_CORE_INFO("SDL_image initialized...");

		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

		_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
		if (_Window == nullptr)
		{
			EG_CORE_ASSERT(false, "Could not create Window.");
		}

		EG_CORE_INFO("Window created...");

		_Renderer = SDL_CreateRenderer(_Window, -1, rendererFlags);
		if (_Renderer == nullptr)
		{
			EG_CORE_ASSERT(false, "Could not create Renderer.");
		}

		EG_CORE_INFO("Renderer created...");

		SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		_IsRunning = true;
		EG_CORE_INFO("Window & Renderer startup successful.");
	}

	void Window::Clear()
	{
		SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(_Renderer);
	}

	void Window::Update()
	{
		SDL_RenderPresent(_Renderer);
		int frameTime = SDL_GetTicks() - _FrameStart;

		if (_FrameRate != 0)
		{
			if (1000 / _FrameRate > frameTime)
			{
				SDL_Delay(1000 / _FrameRate - frameTime);
			}
		}

		_FrameStart = SDL_GetTicks();
	}

	void Window::Close()
	{
		_IsRunning = false;
	}

	bool Window::IsOpen() const
	{
		return _IsRunning;
	}

	void Window::SetFrameRate(int frameRate)
	{
		_FrameRate = frameRate;
	}

	int Window::GetFrameRate() const
	{
		return _FrameRate;
	}

	void Window::SetVSync(bool enabled)
	{
		_VSync = enabled;
		SDL_GL_SetSwapInterval(enabled);
	}

	bool Window::IsVSync() const
	{
		return _VSync;
	}

	void Window::FullScreen(bool enabled)
	{
		SDL_SetWindowFullscreen(_Window, enabled ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	}

	SDL_Renderer** Window::GetRenderer()
	{
		return (&_Renderer);
	}
}