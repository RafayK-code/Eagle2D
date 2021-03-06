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
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();

		EG_CORE_WARN("Window and Renderer Destroyed.");
		EG_CORE_TRACE("Thank you for using Eagle2D. Goodbye!");
	}

	void Window::Init(const char* title, unsigned int width, unsigned int height, Uint32 windowFlags, Uint32 rendererFlags)
	{
		m_FrameRate = 0; m_VSync = false; m_FrameStart = SDL_GetTicks();

		EG_CORE_ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) + 1, "Could not initialize SDL.");

		EG_CORE_INFO("SDL initialized...");

		EG_CORE_ASSERT(IMG_Init(IMG_INIT_PNG), "Coult not initialize SDL_image.");

		EG_CORE_INFO("SDL_image initialized...");

		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

		m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
		if (m_Window == nullptr)
		{
			EG_CORE_ASSERT(false, "Could not create Window.");
		}

		EG_CORE_INFO("Window created...");

		m_Renderer = SDL_CreateRenderer(m_Window, -1, rendererFlags);
		if (m_Renderer == nullptr)
		{
			EG_CORE_ASSERT(false, "Could not create Renderer.");
		}

		EG_CORE_INFO("Renderer created...");

		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		m_IsRunning = true;
		EG_CORE_INFO("Window & Renderer startup successful.");
	}

	void Window::Clear()
	{
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(m_Renderer);
	}

	void Window::Update()
	{
		SDL_RenderPresent(m_Renderer);
		int frameTime = SDL_GetTicks() - m_FrameStart;

		if (m_FrameRate != 0)
		{
			if (1000 / m_FrameRate > frameTime)
			{
				SDL_Delay(1000 / m_FrameRate - frameTime);
			}
		}

		m_FrameStart = SDL_GetTicks();
	}

	void Window::Close()
	{
		m_IsRunning = false;
	}

	bool Window::IsOpen() const
	{
		return m_IsRunning;
	}

	void Window::SetFrameRate(int frameRate)
	{
		m_FrameRate = frameRate;
	}

	int Window::GetFrameRate() const
	{
		return m_FrameRate;
	}

	void Window::SetVSync(bool enabled)
	{
		m_VSync = enabled;
		SDL_GL_SetSwapInterval(enabled);
	}

	bool Window::IsVSync() const
	{
		return m_VSync;
	}

	void Window::FullScreen(bool enabled)
	{
		SDL_SetWindowFullscreen(m_Window, enabled ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	}
}