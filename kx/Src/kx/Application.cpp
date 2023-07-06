#include "Application.h"
#include "stdio.h"
#include "Logger.h"
#include "glad/glad.h"
#include "GlFW/glfw3.h"
#include "kx/input.h"
namespace kx {
	Application* Application::s_Instance = nullptr;
	Application:: Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		unsigned int a;
		glGenVertexArrays(1, &a);
	}
	Application ::~Application() {

	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dis(e);
			dis.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	//	kx_CORE_INFO(e.ToString());

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
			
			for (auto it : m_LayerStack) {
				it->OnUpdate();
			}
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
	
}
