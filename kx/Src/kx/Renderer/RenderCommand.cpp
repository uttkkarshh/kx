
#include "RenderCommand.h"

#include "kx/Platform/Windows/OpenGL/OpenGLRendererAPI.h"

namespace kx {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}