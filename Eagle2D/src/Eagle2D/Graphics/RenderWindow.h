#pragma once
#include "EaglePCH.h"
#include "Eagle2D/Core.h"
#include "SFML/Graphics.hpp"

namespace Eagle
{
	struct WindowProps
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

	class RenderWindow
	{
	public:
		RenderWindow();
		~RenderWindow();

		void Init(const WindowProps& props);
		void Shutdown();

		void OnUpdate();

	private:
		sf::RenderWindow m_RenderWindow;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;
		};

		WindowProps m_Data;
	};
}