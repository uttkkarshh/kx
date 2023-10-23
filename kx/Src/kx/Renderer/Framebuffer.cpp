#include "kx/Renderer/Framebuffer.h"

#include "kx/Renderer/Renderer.h"

#include "kx/Platform/Windows/OpenGL/OpenGLFrameBuffer.h"

namespace kx {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    kx_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(spec);
		}

		kx_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}