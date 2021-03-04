#include "EaglePCH.h"
#include "RendererWindow.h"

namespace Eagle
{
	void RendererWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		m_RenderWindow.create(sf::VideoMode(m_Data.width, m_Data.height), m_Data.title, sf::Style::Default);
		m_RenderWindow.setFramerateLimit(0);
	}

	void RendererWindow::Shutdown()
	{
		m_RenderWindow.close();
	}

	void RendererWindow::OnUpdate()
	{
		m_RenderWindow.clear();
		m_RenderWindow.display();
	}

	bool RendererWindow::IsOpen() const
	{
		return m_RenderWindow.isOpen();
	}

	void RendererWindow::SetFrameRate(int frameRate)
	{
		m_Data.frameRate = frameRate;
		m_RenderWindow.setFramerateLimit(frameRate);
	}

	int RendererWindow::GetFrameRate() const
	{
		return m_Data.frameRate;
	}

	void RendererWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		m_RenderWindow.setVerticalSyncEnabled(enabled);
	}

	bool RendererWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	bool RendererWindow::PollEvent(Event& event)
	{
		return m_RenderWindow.pollEvent(event.GetEvent());
	}
}