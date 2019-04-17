#include "index_buffer.h"
#include <glad/glad.h>

namespace awesome
{
	IndexBuffer::IndexBuffer(const uint* t_data, const uint t_count)
		: m_count(t_count)
	{
		m_size = t_count * sizeof(GLuint);
		// gnerate the buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		// fill the buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, t_data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint IndexBuffer::id() const
	{
		return m_id;
	}

	std::size_t IndexBuffer::size() const
	{
		return m_size;
	}

	uint IndexBuffer::count() const
	{
		return m_count;
	}
}