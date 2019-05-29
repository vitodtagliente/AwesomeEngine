#include "renderable_gl.h"

#include "opengl.h"
#include "graphics_buffer_gl.h"

namespace awesome
{
	RenderableGL::RenderableGL(GraphicsBuffer* const t_vertex, GraphicsBuffer* const t_index)
		: Renderable(t_vertex, t_index)
		, m_id()
	{
		glGenVertexArrays(1, &m_id);
		bind();

		t_vertex->bind();

		const auto& elements = t_vertex->layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			const auto& element = elements[i];
			unsigned int element_type{};
			switch (element.type)
			{
			case GraphicsBufferElement::Type::Char:
				element_type = GL_BYTE;
				break;
			case GraphicsBufferElement::Type::Integer:
				element_type = GL_INT;
				break;
			case GraphicsBufferElement::Type::UnsignedInteger:
				element_type = GL_UNSIGNED_INT;
				break;
			default:
			case GraphicsBufferElement::Type::Float:
				element_type = GL_FLOAT;
				break;
			}

			glVertexAttribPointer(i, element.count, element_type,
				element.normalized ? GL_TRUE : GL_FALSE,
				t_vertex->layout.getStride(),
				(const void*)offset
			);

			glEnableVertexAttribArray(i);

			offset += element.size;
		}
		
		t_index->bind();

		t_vertex->unbind();
		t_index->unbind();
		unbind();
	}

	RenderableGL::~RenderableGL()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void RenderableGL::bind()
	{
		glBindVertexArray(m_id);
	}

	void RenderableGL::unbind()
	{
		glBindVertexArray(0);
	}
}