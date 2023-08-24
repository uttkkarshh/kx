#include "Application.h"
#include "stdio.h"
#include "Logger.h"
#include "kx/Renderer/Renderer.h"
#include "GlFW/glfw3.h"
#include "kx/Core/input.h"

namespace kx {
	Application* Application::s_Instance = nullptr;
	
	Application:: Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		Renderer::Init();
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}
	Application ::~Application() {

	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dis(e);
			dis.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
			dis.Dispatch<WindowResizeEvent>(KX_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run() { 
		WindowResizeEvent w = WindowResizeEvent(400, 22);
		kx_CORE_TRACE(w.ToString());
		 std::pair<float ,float> p= Input::GetMousePosition();
		
		 while (m_running)
		 {


			 float time = (float)glfwGetTime();
			 Timestep timestep = time - m_LastFrameTime;
			 m_LastFrameTime = time;
			 if (!m_Minimized){
				 for (auto it : m_LayerStack) {
					 it->OnUpdate(timestep);
				 }
		 }
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
		}

		

	bool Application::OnWindowClose(WindowCloseEvent& w)
	{
		
			m_running = false;
			return true;
		
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
