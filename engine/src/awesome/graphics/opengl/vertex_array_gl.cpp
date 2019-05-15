#include "vertex_array_gl.h"

#include "opengl.h"
#include "vertex_buffer_gl.h"
#include "../vertex_buffer_layout.h"

namespace awesome
{
	VertexArrayGL::VertexArrayGL()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArrayGL::~VertexArrayGL()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArrayGL::bind()
	{
		glBindVertexArray(m_id);
	}

	void VertexArrayGL::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArrayGL::add(VertexBuffer* const t_buffer, VertexBufferLayout* const t_layout)
	{
		bind();
		t_buffer->bind();
		const auto& elements = t_layout->getElements();
		uint offset = 0;
		for (uint i = 0; i < elements.size(); ++i)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);

			unsigned int element_type{};
			switch (element.type)
			{
			case VertexBufferElement::Type::Char:
				element_type = GL_BYTE;
				break;
			case VertexBufferElement::Type::Integer:
				element_type = GL_INT;
				break;
			case VertexBufferElement::Type::UnsignedInteger:
				element_type = GL_UNSIGNED_INT;
				break;
			default:
			case VertexBufferElement::Type::Float:
				element_type = GL_FLOAT;
				break;
			}

			glVertexAttribPointer(i, element.count, element_type,
				element.normalized ? GL_TRUE : GL_FALSE,
				t_layout->getStride(),
				(const void*)offset
			);
			offset += element.size;
		}
	}
}