#include "Renderer2D.h"
#include "VertexArray.h"
#include "shader.h"
#include <kx/Platform/Windows/OpenGL/OpenGLShader.h>
#include "kx/Renderer/RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>
namespace kx {
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Texture2D> WhiteTexture;
		Ref<Shader>TexShader;
	};

	static Renderer2DStorage* s_Data;
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = kx::VertexArray::Create();
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,0.0,0.0,
			 0.5f, -0.5f, 0.0f,1.0,0.0,
			 0.5f,  0.5f, 0.0f,1.0,1.0,
			-0.5f,  0.5f, 0.0f,0.0,1.0
		};

		kx::Ref<kx::VertexBuffer> squareVB;
		squareVB.reset(kx::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ kx::ShaderDataType::Float3, "a_Position" },
			{ kx::ShaderDataType::Float2, "a_Texture" }
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		kx::Ref<kx::IndexBuffer> squareIB;
		squareIB.reset(kx::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		
		s_Data->TexShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetInt("u_Texture", 0);


	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{

		
		
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data->TexShader->SetMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TexShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D>& texture)
	{
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data->TexShader->SetInt("u_Texture", 0);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TexShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}