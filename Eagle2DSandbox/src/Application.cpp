#include <Eagle2D.h>

class Sandbox : public Eagle::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

Eagle::Application* Eagle::CreateApplication()
{
	return new Sandbox();
}