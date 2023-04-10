#include "Application.h"
#include "stdio.h"
#include "Logger.h"
#include "Event/ApplicationEvent.h"
namespace kx {
	Application:: Application()
	{

	}
	Application ::~Application() {

	}
	void Application::Run() {
		WindowResizeEvent w = WindowResizeEvent(400, 22);
		kx_CORE_TRACE(w.ToString());
		while (true)
		{
			
		}
	    }
}
