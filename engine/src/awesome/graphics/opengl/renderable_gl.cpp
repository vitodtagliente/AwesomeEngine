#include "renderable_gl.h"

#include <vector>
#include "opengl.h"
#include "graphics_buffer_gl.h"
#include "../mesh/mesh.h"

namespace awesome
{
	RenderableGL::RenderableGL()
		: Renderable()
		, m_vao()
		, m_vbo()
		, m_ebo()
	{
	}

	RenderableGL::RenderableGL(const Mesh& t_mesh)
		: Renderable(t_mesh)
		, m_vao()
		, m_vbo()
		, m_ebo()
	{
		// get mesh vertex data
		std::vector<float> vertex_data;
		t_mesh.getData(vertex_data);
		// generate the vertex array object
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		// bind buffers
		bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER
			, sizeof(float) * vertex_data.size()
			, &vertex_data.front()
			, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER
			, t_mesh.indices.size() * sizeof(unsigned int)
			, &t_mesh.indices.front()
			, GL_STATIC_DRAW);

		// vertex positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// vertex texture coords
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unbind();
	}

	RenderableGL::~RenderableGL()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}

	void RenderableGL::bind()
	{
		glBindVertexArray(m_vao);
	}

	void RenderableGL::unbind()
	{
		glBindVertexArray(0);
	}
}