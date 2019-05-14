#include "index_buffer_gl.h"

#include "opengl.h"

namespace awesome
{
	IndexBufferGL::IndexBufferGL(const unsigned int * const t_data, const unsigned int t_count)
		: IndexBuffer(t_data, t_count)
	{
		m_size = t_count * sizeof(GLuint);
		// gnerate the buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		// fill the buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, t_data, GL_STATIC_DRAW);
	}

	IndexBufferGL::~IndexBufferGL()
	{
		glDeleteBuffers(1, &m_id);
	}

	void IndexBufferGL::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBufferGL::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}