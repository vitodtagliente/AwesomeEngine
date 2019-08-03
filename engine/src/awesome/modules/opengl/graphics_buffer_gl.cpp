#include "graphics_buffer_gl.h"

#include "opengl.h"

namespace awesome
{
	GraphicsBufferGL::GraphicsBufferGL(const Type t_type, const void* const t_data, const std::size_t t_size)
		: GraphicsBuffer(t_type, t_data, t_size)
		, m_id()
		, m_nativeType()
	{
		glGenBuffers(1, &m_id);

		switch (t_type)
		{
		case GraphicsBuffer::Type::Index:
			m_nativeType = GL_ELEMENT_ARRAY_BUFFER;
			break;
		default:
		case GraphicsBuffer::Type::Vertex:
			m_nativeType = GL_ARRAY_BUFFER;
			break;
		}

		bind();
		glBufferData(m_nativeType, t_size, t_data, GL_STATIC_DRAW);
	}

	GraphicsBufferGL::~GraphicsBufferGL()
	{
		glDeleteBuffers(1, &m_id);
	}

	void GraphicsBufferGL::bind()
	{
		glBindBuffer(m_nativeType, m_id);
	}

	void GraphicsBufferGL::unbind()
	{
		glBindBuffer(m_nativeType, 0);
	}
}