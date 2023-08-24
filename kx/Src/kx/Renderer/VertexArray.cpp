#include "VertexArray.h"

#include "Renderer.h"
#include "kx/Platform/Windows/OpenGL/OpenGLVertexArray.h"
#include "kx/Core/Core.h"
#include "kx/Core/Logger.h"
namespace kx {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    kx_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		kx_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}