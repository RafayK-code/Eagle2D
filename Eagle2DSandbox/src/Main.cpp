#include <Eagle2D.h>
#include <iostream>

class Sandbox
{
public:
	Sandbox(const char* title, int width, int height)
	{
		m_Window.Init(Eagle::WindowProps(title, width, height));
		m_Window.SetFrameRate(60);
	}

	~Sandbox()
	{
	}

	void Run()
	{
		//SAMPLE WINDOW USING EAGLE
		while (m_Window.IsOpen())
		{
			Eagle::Event event;
			while (m_Window.PollEvent(event))
			{
				switch (event.GetEvent().type)
				{
				case Eagle::Event::Closed:
					m_Window.Shutdown();
					break;
				case Eagle::Event::KeyPressed:
					switch (event.GetEvent().key.code)
					{
					case Eagle::Keyboard::A:
						printf("They Pressed A.");
						break;
					}
				}
			}
			m_Window.OnUpdate();
		}
	}

private:
	Eagle::RendererWindow m_Window;
};

int main(int agrc, char** argv)
{
	Sandbox* sandbox = new Sandbox("App", 1280, 720);
	sandbox->Run();
	delete sandbox;

	return 0;
}