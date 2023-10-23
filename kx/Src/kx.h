#pragma once
#include "kx/Core/Core.h"
#include "kx/Core/Application.h"

#include "kx/Core/Logger.h"
#include "kx/Event/Event.h"
#include "kx/Event/ApplicationEvent.h"
#include "kx/Imgui/ImGuiLayer.h"
#include "kx/Event/KeyEvent.h"
#include "kx/Event/MouseEvent.h"
#include "kx/Core/KeyCodes.h"
#include "kx/Core/MouseButtonCodes.h"
#include "kx/Core/input.h"

//Debug
#include "kx/Debug/Instrumentor.h"


// ---Renderer------------------------
#include "kx/Renderer/Renderer.h"
#include "kx/Renderer/RenderCommand.h"
#include "kx/Renderer/Renderer2D.h"

#include "kx/Renderer/Buffer.h"
#include "kx/Renderer/Shader.h"
#include "kx/Renderer/VertexArray.h"
#include "kx/Renderer/Framebuffer.h"
#include "kx/Platform/Windows/OpenGL/OpenGLShader.h"


#include "kx/Renderer/OrthographicCameraController.h"
#include "kx/Renderer/OrthographicCamera.h"
#include "kx/Renderer/Texture.h"