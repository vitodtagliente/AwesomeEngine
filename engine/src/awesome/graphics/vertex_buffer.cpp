#include "vertex_buffer.h"
#include <glad/glad.h>

namespace awesome
{
	VertexBuffer::VertexBuffer(const void* t_data, const std::size_t t_size, const AccessMode t_access)
	{
		// generate the buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		// fill the buffer with the data
		uint access_mode = 0;
		switch(t_access)
		{ 
		case AccessMode::StaticDraw:
			access_mode = GL_STATIC_DRAW;
			break;
		}
		glBufferData(GL_ARRAY_BUFFER, t_size, t_data, access_mode);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	uint VertexBuffer::getId() const
	{
		return m_id;
	}
}