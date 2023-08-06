#include "kx.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>


class ExampleLayer :public  kx::Layer {
public:
	ExampleLayer()
		:Layer("From Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(kx::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		kx::Ref<kx::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(kx::VertexBuffer::Create(vertices, sizeof(vertices)));
		kx::BufferLayout layout = {
			{ kx::ShaderDataType::Float3, "a_Position" },
			{ kx::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		kx::Ref<kx::IndexBuffer> indexBuffer;
		indexBuffer.reset(kx::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(kx::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		kx::Ref<kx::VertexBuffer> squareVB;
		squareVB.reset(kx::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ kx::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		kx::Ref<kx::IndexBuffer> squareIB;
		squareIB.reset(kx::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);
		float texVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		kx::Ref<kx::VertexBuffer> texVB;
		texVB.reset(kx::VertexBuffer::Create(texVertices, sizeof(texVertices)));
		texVB->SetLayout({ {kx::ShaderDataType::Float3,"a_position"},
                  {  kx::ShaderDataType::Float2 ,"a_texture"}});
		m_TexVA.reset(kx::VertexArray::Create());
		m_TexVA->AddVertexBuffer(texVB);
		uint32_t texIndices[6] = { 0, 1, 2, 2, 3, 0 };
		kx::Ref<kx::IndexBuffer> texIB;
		texIB.reset(kx::IndexBuffer::Create(texIndices, sizeof(texIndices) / sizeof(uint32_t)));
		m_TexVA->SetIndexBuffer(texIB);
		

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader=kx::Shader::Create("1",vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
            uniform vec3 u_Color; 

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			uniform sampler2D u_Texture;
			
			void main()
			{
              color = color = texture(u_Texture, v_TexCoord);

			}
		)";

		m_BlueShader= kx::Shader::Create("Blue",blueShaderVertexSrc, blueShaderFragmentSrc);
		m_texShader=m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_Texture = kx::Texture2D::Create("assets/textures/Checkerboard.png");
		m_avtar = kx::Texture2D::Create("assets/textures/avtar.png");
		std::dynamic_pointer_cast<kx::OpenGLShader>(m_texShader)->Bind();
		std::dynamic_pointer_cast<kx::OpenGLShader>(m_texShader)->UploadUniformInt("u_Texture", 0);
	}
	void OnUpdate(kx::Timestep ts)  override
	{   
		if (kx::Input::IsKeyPressed(KX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed *ts ;
		else if (kx::Input::IsKeyPressed(KX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed *ts;

		if (kx::Input::IsKeyPressed(KX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed *ts;
		else if (kx::Input::IsKeyPressed(KX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed *ts;

		if (kx::Input::IsKeyPressed(KX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed *ts ;
		if (kx::Input::IsKeyPressed(KX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed *ts;
		kx::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		kx::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		kx::Renderer::BeginScene(m_Camera);

		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		std::dynamic_pointer_cast<kx::OpenGLShader>(m_BlueShader)->Bind();
		std::dynamic_pointer_cast<kx::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			//	kx::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			//	kx::Renderer::Submit(m_Shader, m_VertexArray,transform);
				m_Texture->Bind();
				kx::Renderer::Submit(m_texShader, m_TexVA);
				m_avtar->Bind();
				kx::Renderer::Submit(m_texShader, m_TexVA);
			}
		}
	

		kx::Renderer::EndScene();
		
	}
	
	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
		}
	
	void OnEvent(kx::Event& event)   override {
		

	}
private:
	kx::ShaderLibrary m_ShaderLibrary;



	kx::Ref<kx::Shader> m_Shader;
	kx::Ref<kx::VertexArray> m_VertexArray;

	kx::Ref<kx::Shader> m_BlueShader;
	kx::Ref<kx::VertexArray> m_SquareVA;

	kx::Ref<kx::Shader> m_texShader;
	kx::Ref<kx::VertexArray> m_TexVA;

	kx::Ref<kx::Texture2D> m_Texture,m_avtar;
	kx::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class sand : public kx::Application {
public:
	sand() {
		PushLayer(new ExampleLayer());
		
	}
	~sand() {

	}
};
kx::Application* kx::CreateApplication() {
	return  new sand;


}