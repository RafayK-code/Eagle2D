#pragma once
#include "Core.h"

namespace Eagle
{
	class EAGLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	//TO BE DEFINED IN CLIENT
	Application* CreateApplication();
}