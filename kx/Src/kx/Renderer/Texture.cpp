#include "Texture.h"

#include "Renderer.h"
#include "kx/Platform/Windows/OpenGL/OpenGLTexture.h"

namespace kx {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    kx_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		kx_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    kx_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(width, height);
		}

		kx_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}