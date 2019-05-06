#include "vertex_buffer_gl.h"

#include "opengl.h"

namespace awesome
{
	VertexBufferGL::VertexBufferGL(const void* const t_data, const std::size_t t_size, const AccessMode t_mode)
		: VertexBuffer(t_data, t_size, t_mode)
	{
		// generate the buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		// fill the buffer with the data
		unsigned int access_mode = 0;
		switch (t_mode)
		{
		case AccessMode::StaticDraw:
			access_mode = GL_STATIC_DRAW;
			break;
		}
		glBufferData(GL_ARRAY_BUFFER, t_size, t_data, access_mode);
	}

	VertexBufferGL::~VertexBufferGL()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBufferGL::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBufferGL::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}