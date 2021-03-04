#include <Eagle2D.h>
#include <iostream>

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

int main(int agrc, char** argv)
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;

	return 0;
}