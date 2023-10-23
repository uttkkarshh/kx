#pragma once
#include "Core.h"

#include "kx/Imgui/ImGuiLayer.h"
#include "kx/Platform/Windows/WindowsWindow.h"
#include "LayerStack.h"
#include "kx/Renderer/shader.h"
#include "kx/Renderer/Buffer.h"
#include "kx/Renderer/VertexArray.h"
#include "kx/Renderer/OrthographicCamera.h"
#include "kx/Core/Timestep.h"

namespace kx {
	
	class kx_API Application
	{
	public:
		Application(std::string name);

		~Application();
		void OnEvent(Event &e);
		void Run();
		bool OnWindowClose(WindowCloseEvent &w);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		bool OnWindowResize(WindowResizeEvent& e);
		inline static Application& Get() { return *s_Instance; }
		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		float m_LastFrameTime = 0.0f;
	};
	Application* CreateApplication();
}
