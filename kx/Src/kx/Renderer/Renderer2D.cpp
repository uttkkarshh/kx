#include "Renderer2D.h"
#include "VertexArray.h"
#include "shader.h"
#include <kx/Platform/Windows/OpenGL/OpenGLShader.h>
#include "kx/Renderer/RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>
namespace kx {
	struct QuadVertex{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DStorage
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<VertexArray> QuadVertexArray;
		Ref<Texture2D> WhiteTexture;
		Ref<Shader>TexShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		
		glm::vec4 QuadVertexPositions[4];

		static const uint32_t MaxTextureSlots = 32;
		std::array<Ref<Texture2D>, MaxTextureSlots > TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture
		Renderer2D::Statistics Stats;
	};

	static Renderer2DStorage* s_Data;
	void Renderer2D::Init()
	{
		


		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = kx::VertexArray::Create();
		s_Data->WhiteTexture = Texture2D::Create(1, 1);

		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


		

		s_Data->QuadVertexBuffer.reset(kx::VertexBuffer::Create( s_Data->MaxVertices*sizeof(QuadVertex)));
		s_Data->QuadVertexBuffer->SetLayout({
			{ kx::ShaderDataType::Float3, "a_Position" },
			{ kx::ShaderDataType::Float4, "a_Colour" },
			{ kx::ShaderDataType::Float2, "a_Texture" }
			,
			{ kx::ShaderDataType::Float, "a_TexIndex" },
			{ kx::ShaderDataType::Float, "a_TilingFactor" }
			});
		
		s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);
		s_Data->QuadVertexBufferBase = new QuadVertex[s_Data->MaxVertices];


		s_Data->QuadVertexBufferBase = new QuadVertex[s_Data->MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data->MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data->MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB;
		quadIB.reset(IndexBuffer::Create(quadIndices, s_Data->MaxIndices));
		s_Data->QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		s_Data->QuadVertexArray->SetIndexBuffer(quadIB);
		int32_t samplers[s_Data->MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data->MaxTextureSlots; i++)
			samplers[i] = i;
		
		s_Data->TexShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TexShader->Bind();
		
		s_Data->TexShader->SetIntArray("u_Textures", samplers, s_Data->MaxTextureSlots);

		// Set all texture slots to 0
		s_Data->TextureSlots[0] = s_Data->WhiteTexture;
		s_Data->QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data->QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;
		
		
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data->TexShader->SetMat4("u_Transform", glm::mat4(1.0f));
		s_Data->TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{


		uint32_t dataSize = (uint8_t*)s_Data->QuadVertexBufferPtr - (uint8_t*)s_Data->QuadVertexBufferBase;
		s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBase, dataSize);
		
		Flush();
		
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++)
			s_Data->TextureSlots[i]->Bind(i);
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->QuadIndexCount);
		s_Data->Stats.DrawCalls++;
	}
	

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (s_Data->QuadIndexCount >= Renderer2DStorage::MaxIndices)
			FlushAndReset();
		const float texIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;
		glm::mat4 transform = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), { size.x,size.y,1.0 });
		s_Data->QuadVertexBufferPtr->Position = transform*s_Data->QuadVertexPositions[0];
	s_Data->QuadVertexBufferPtr->Color = color;
	s_Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
	s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
	s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	s_Data->QuadVertexBufferPtr++;

	s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[1];
	s_Data->QuadVertexBufferPtr->Color = color;
	s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
	s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
	s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	s_Data->QuadVertexBufferPtr++;

	s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[2];
	s_Data->QuadVertexBufferPtr->Color = color;
	s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
	s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
	s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	s_Data->QuadVertexBufferPtr++;

	s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[3];
	s_Data->QuadVertexBufferPtr->Color = color;
	s_Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
	s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
	s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	s_Data->QuadVertexBufferPtr++;

	s_Data->QuadIndexCount += 6;
	s_Data->Stats.QuadCount++;

	/*	s_Data->TexShader->Bind();
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TexShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);*/
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		if (s_Data->QuadIndexCount >= Renderer2DStorage::MaxIndices)
			FlushAndReset();
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data->TextureSlotIndex; i++)
		{
			if (*s_Data->TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data->TextureSlotIndex;
			s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
			s_Data->TextureSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), { size.x,size.y,1.0 });
		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[0];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position =  transform * s_Data->QuadVertexPositions[1];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[2];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[3];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadIndexCount += 6;
		s_Data->Stats.QuadCount++;
#if OLD_PATH
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetFloat4("u_Color", tintColor);
		s_Data->TexShader->SetInt("u_Texture", 0);
		s_Data->TexShader->SetFloat("u_TilingFactor", tilingFactor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TexShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
#endif
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position,1.0f), size, rotation, color);

	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();
		s_Data->TexShader->SetInt("u_Texture", 0);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TexShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size,rotation, texture, tilingFactor, tintColor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		if (s_Data->QuadIndexCount >= Renderer2DStorage::MaxIndices)
			FlushAndReset();
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data->TextureSlotIndex; i++)
		{
			if (*s_Data->TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data->TextureSlotIndex;
			s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
			s_Data->TextureSlotIndex++;
	}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[0];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[1];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[2];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPositions[3];
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadIndexCount += 6;
		s_Data->Stats.QuadCount++;

#if OLD_PATH
		s_Data->TexShader->Bind();
		s_Data->TexShader->SetFloat4("u_Color", tintColor);
		s_Data->TexShader->SetInt("u_TilingFactor", tilingFactor);
		s_Data->TexShader->SetInt("u_Texture", 0);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->TexShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	
#endif}
}

void Renderer2D::ResetStats()
{
	memset(&s_Data->Stats, 0, sizeof(Statistics));
}

Renderer2D::Statistics Renderer2D::GetStats()
{
	return s_Data->Stats;
}
void Renderer2D::FlushAndReset()
{
	EndScene();

	s_Data->QuadIndexCount = 0;
	s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;

	s_Data->TextureSlotIndex = 1;
}
}