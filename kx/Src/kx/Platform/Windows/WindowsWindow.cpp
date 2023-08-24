#include "WindowsWindow.h"
#include "kx/Event/ApplicationEvent.h"
#include "kx/Event/KeyEvent.h"
#include "kx/Event/MouseEvent.h"

#include "kx/Platform/Windows/OpenGL/OpenGLContext.h"
namespace kx {
	static void GLFWErrorCallBack(int error, const char* description) {
		kx_CORE_TRACE(description);
	}
	static bool s_GLFWInitialized = false;
	 Window * Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
		
	}
	

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
		
	}
	
	void WindowsWindow::SetVSync(bool enabled) const
	{
		if (enabled) {
			glfwSwapInterval(1);

		}
		else {
			glfwSwapInterval(0);
		}
	
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height; 
		kx_CORE_TRACE("creating Window");
	    
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallBack);
			s_GLFWInitialized = true;

		}
		m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
			
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		//calllbacks
		//p = m_Window;
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow*  window, int width, int height) {
			WindowData& d=*(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent e(width,height);
			d.EventCallback(e);
			d.Width = width;
			d.Height = height;
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData & d = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			d.EventCallback(e);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int key ,int Scancode ,int action,int mods){
			WindowData& d = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS :
			{   KeyPressedEvent event(key, 0);
			d.EventCallback(event);
				break; }
			case GLFW_RELEASE:
			{ KeyReleasedEvent event(key);
			d.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
				KeyPressedEvent event(key, 0);
				d.EventCallback(event);
				break;
			}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& d = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{   MouseButtonPressedEvent event(button);
			d.EventCallback(event);
			break; }
			case GLFW_RELEASE:
			{ MouseButtonReleasedEvent event(button);
			d.EventCallback(event);
			break;
			}
			}
		
			});

		glfwSetScrollCallback(m_Window,[](GLFWwindow* window,double xOffset, double yOffset) {
			WindowData& d = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			d.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& d = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			d.EventCallback(event);
			});
	
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
	
	


}