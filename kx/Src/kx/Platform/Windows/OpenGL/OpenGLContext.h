#pragma once
#include "kx/Renderer/GraphicsContext.h"
struct GLFWwindow;
namespace  kx {
	class OpenGLContext :public GraphicsContext 
	{ public:
		virtual void Init() override;
		virtual void SwapBuffers() override;
		OpenGLContext(GLFWwindow* windowhandle);

	private :
		GLFWwindow* m_WindowHandle;
	};

}