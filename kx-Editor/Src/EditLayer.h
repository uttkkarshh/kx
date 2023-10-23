#pragma once
#include "kx.h"
#include "kx\Core\Layer.h"
class EditorLayer :public kx::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

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
	glm::vec2 m_ViewPortSize = { 0.0,0.0 };
	bool m_ViewportFocused = false, m_ViewportHovered = false;
	
};

