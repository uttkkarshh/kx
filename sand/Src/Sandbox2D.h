#pragma once
#include "kx.h"
#include "kx\Core\Layer.h"
class Sandbox2D :public kx::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(kx::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(kx::Event& e) override;
private:
	kx::OrthographicCameraController m_CameraController;
	kx::Ref<kx::Texture2D> m_Texture;
	// Temp
	kx::Ref<kx::VertexArray> m_SquareVA;
	kx::Ref<kx::Shader> m_FlatColorShader;
	kx::Ref<kx::Framebuffer> m_Framebuffer;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	

	
};

