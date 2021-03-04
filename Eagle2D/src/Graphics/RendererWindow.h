#pragma once
#include "EaglePCH.h"
#include "Core/Core.h"
#include "SFML/Graphics.hpp"
#include "Core/Event.h"

namespace Eagle
{
	struct EAGLE_API WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Eagle2D",
					unsigned int width = 1280,
					unsigned int height = 720)
			: title(title), width(width), height(height)
		{}
	};

	class EAGLE_API RendererWindow
	{
	public:
		void Init(const WindowProps& props);
		void Shutdown();

		void OnUpdate();

		bool IsOpen() const;

		void SetFrameRate(int frameRate);
		int GetFrameRate() const;

		void SetVSync(bool enabled);
		bool IsVSync() const;

		bool PollEvent(Event& event);

	private:
		sf::RenderWindow m_RenderWindow;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;
			int frameRate;
		};

		WindowData m_Data;
	};
}