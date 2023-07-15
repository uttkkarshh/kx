#pragma once
#include "Core.h"

#include "kx/Imgui/ImGuiLayer.h"
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
		ImGuiLayer* m_ImGuiLayer;
		bool m_running=true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};
	Application* CreateApplication();
}
