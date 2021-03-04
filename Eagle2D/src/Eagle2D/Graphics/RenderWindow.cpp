#include "EaglePCH.h"
#include "RenderWindow.h"

namespace Eagle
{
	RenderWindow::RenderWindow()
	{
	}

	RenderWindow::~RenderWindow()
	{
	}

	void RenderWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		m_RenderWindow.create(sf::VideoMode(m_Data.width, m_Data.height), m_Data.title, sf::Style::Default);
		m_RenderWindow.setFramerateLimit(60);
	}

	void RenderWindow::Shutdown()
	{
		m_RenderWindow.close();
	}

	void RenderWindow::OnUpdate()
	{
		//This function will be different, but for now it just keeps the window open, polls events and draws to it
		while (m_RenderWindow.isOpen())
		{
			sf::Event event;
			while (m_RenderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					Shutdown();
				}
			}
			m_RenderWindow.clear();
			m_RenderWindow.display();
		}
	}
}