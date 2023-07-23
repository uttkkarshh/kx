#include "VertexArray.h"

#include "Renderer.h"
#include "kx/Platform/Windows/OpenGL/OpenGLVertexArray.h"
#include "kx/Core.h"
#include "kx/Logger.h"
namespace kx {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    kx_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		kx_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}