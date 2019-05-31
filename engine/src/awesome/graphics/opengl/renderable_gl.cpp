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
		glBufferData(GL_ARRAY_BUFFER, vertex_data.capacity(), vertex_data.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_mesh.indices.size() * sizeof(unsigned int),
			t_mesh.indices.data(), GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vector3), (void*)0);
		// vertex texture coords
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vector2), (void*)sizeof(vector3));

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