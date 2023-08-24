#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "kx/Core/Logger.h"
void kx::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	kx_CORE_ASSERT(status, "Failed to initialize Glad!");

	kx_CORE_INFO("OpenGL Info:");
	kx_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
	kx_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	kx_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
}

void kx::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

kx::OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
	:m_WindowHandle(windowhandle)
{
}
