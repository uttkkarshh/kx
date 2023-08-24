#include "OpenGLVertexArray.h"
#include "kx/Core/Core.h"
#include "kx/Core/Logger.h"
#include <glad/glad.h>
namespace kx {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case kx::ShaderDataType::Float:    return GL_FLOAT;
		case kx::ShaderDataType::Float2:   return GL_FLOAT;
		case kx::ShaderDataType::Float3:   return GL_FLOAT;
		case kx::ShaderDataType::Float4:   return GL_FLOAT;
		case kx::ShaderDataType::Mat3:     return GL_FLOAT;
		case kx::ShaderDataType::Mat4:     return GL_FLOAT;
		case kx::ShaderDataType::Int:      return GL_INT;
		case kx::ShaderDataType::Int2:     return GL_INT;
		case kx::ShaderDataType::Int3:     return GL_INT;
		case kx::ShaderDataType::Int4:     return GL_INT;
		case kx::ShaderDataType::Bool:     return GL_BOOL;
		}

	 kx_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		kx_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index + m_VertexBufferIndexOffset);
			glVertexAttribPointer(index + m_VertexBufferIndexOffset,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}


		m_VertexBuffers.push_back(vertexBuffer);
		m_VertexBufferIndexOffset += layout.GetElements().size();
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}





}