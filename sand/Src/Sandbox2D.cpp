#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "kx/Platform/Windows/OpenGL/OpenGLShader.h"

#include <chrono>



Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = kx::Texture2D::Create("assets/textures/Checkerboard.png");
	kx::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = kx::Framebuffer::Create(fbSpec);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(kx::Timestep ts)
{
	kx_PROFILE_FUNCTION();
	kx::Renderer2D::ResetStats();
	// Update
	{
		kx_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	m_Framebuffer->Bind();
	// Render
	{
		kx_PROFILE_SCOPE("Renderer Prep");
		kx::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		kx::RenderCommand::Clear();
	}

	{
		kx_PROFILE_SCOPE("Renderer Draw");
		kx::Renderer2D::BeginScene(m_CameraController.GetCamera());
		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		kx::Renderer2D::BeginScene(m_CameraController.GetCamera());
		kx::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		kx::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		kx::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		kx::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 10.0f);
		kx::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture, 20.0f);
		kx::Renderer2D::EndScene();

		kx::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				kx::Renderer2D::DrawQuad({ x, y }, { 0.40f, 0.40f }, color);
			}
		}
		kx::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}
	
}

	

void Sandbox2D::OnImGuiRender()
{

}

void Sandbox2D::OnEvent(kx::Event& e)
{
	m_CameraController.OnEvent(e);
}