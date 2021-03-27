#pragma once
#include <SDL.h>

namespace Eagle
{
	//Creates a window and a 2D rendering target
	class EAGLE_API Window
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

		SDL_Renderer** GetRenderer();

		float dt;

	private:
		SDL_Window* _Window;
		SDL_Renderer* _Renderer;

		bool _IsRunning;

		int _FrameRate;
		bool _VSync;

		Uint32 _FrameStart;

		friend class PhysicsSystem;
		friend class AssetManager;
		friend class LightingSystem;
		friend class ParticleSystem;
	};
}