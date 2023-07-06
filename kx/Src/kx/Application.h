#pragma once
#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Platform/Windows/WindowsWindow.h"
#include "LayerStack.h"
namespace kx {
	class kx_API Application
	{
	public:
		Application();

		~Application();
		void OnEvent(Event &e);
		void Run();
		bool OnWindowClose(WindowCloseEvent &w);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		std::unique_ptr<Window> m_Window;
		bool m_running=true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};
	Application* CreateApplication();
}
