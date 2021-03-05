#include "Window.h"

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
	}

	void Window::Init(const char* title, unsigned int width, unsigned int height, Uint32 windowFlags, Uint32 rendererFlags)
	{
		m_FrameRate = 0; m_VSync = false; m_FrameStart = SDL_GetTicks();

		SDL_Init(SDL_INIT_VIDEO);

		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

		m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
		m_Renderer = SDL_CreateRenderer(m_Window, -1, rendererFlags);
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		m_IsRunning = true;
	}

	void Window::Clear()
	{
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