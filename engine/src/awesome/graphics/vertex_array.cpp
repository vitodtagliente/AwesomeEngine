#include "vertex_array.h"
#include <glad/glad.h>
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace awesome
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	uint VertexArray::id() const
	{
		return m_id;
	}
	
	void VertexArray::add(const VertexBuffer& t_buffer, const VertexBufferLayout& t_layout)
	{
		bind();
		t_buffer.bind();
		const auto& elements = t_layout.getElements();
		uint offset = 0;
		for (uint i = 0; i < elements.size(); ++i)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type,
				element.normalized ? GL_TRUE : GL_FALSE,
				t_layout.getStride(),
				(const void*)offset
			);
			offset += element.size;
		}
	}
}