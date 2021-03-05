#pragma once
#include <SDL.h>

namespace Eagle
{
	//Creates a window and a 2D rendering target
	class Window
	{
	public:
		Window();
		Window(const char* title, unsigned int width, unsigned int height, Uint32 windowFlags, Uint32 rendererFlags);
		~Window();

		void Init(const char* title, unsigned int width, unsigned int height, Uint32 windowFlags, Uint32 rendererFlags);

		void Clear();
		void Update();

		void Close();
		bool IsOpen() const;

		void SetFrameRate(int frameRate);
		int GetFrameRate() const;

		void SetVSync(bool enabled);
		bool IsVSync() const;

		void FullScreen(bool enabled);

		static SDL_Renderer* m_Renderer;

	private:
		SDL_Window* m_Window;

		bool m_IsRunning;

		int m_FrameRate;
		bool m_VSync;

		Uint32 m_FrameStart;
	};
}