#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "kx/Platform/Windows/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = kx::Texture2D::Create("assets/textures/Checkerboard.png");
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(kx::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	kx::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	kx::RenderCommand::Clear();

	kx::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	kx::Renderer2D::DrawQuad({ 0.0f, 0.0f ,0.0f}, { 10.0f, 10.0f }, m_Texture);
	kx::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 3.0f, 3.0f }, { 0.1f, 0.0f, 0.3f, 1.0f });
	kx::Renderer2D::EndScene();
}

	

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(kx::Event& e)
{
	m_CameraController.OnEvent(e);
}