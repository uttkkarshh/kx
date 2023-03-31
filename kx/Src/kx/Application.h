#pragma once
#include "Core.h"
namespace kx {
	class kx_API Application
	{
	public:
		Application();

		~Application();

		void Run();
	};
	Application* CreateApplication();
}
