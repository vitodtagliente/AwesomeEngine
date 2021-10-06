#include "vertex_buffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(size_t size, BufferUsageMode mode)
	: Buffer(size, mode)
	, layout()
	, m_id()
{
	GLenum usage = 0;
	switch (mode)
	{
	case BufferUsageMode::Dynamic: usage = GL_DYNAMIC_DRAW; break;
	case BufferUsageMode::Stream: usage = GL_STREAM_DRAW; break;
	case BufferUsageMode::Static:
	default:
		usage = GL_STATIC_DRAW; break;
	}

	glGenBuffers(1, &m_id);
	bind();
	glBufferData(
		GL_ARRAY_BUFFER,
		size,
		nullptr,
		usage
	);
}

VertexBuffer::~VertexBuffer()
{
	free();
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::free()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::fillData(void* const data, size_t size)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::fillSubData(void* const data, size_t size, int offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::activateLayout(int startingIdex)
{
	int elementIndex = startingIdex;
	int offset = 0;

	for (const VertexBufferElement& element : layout.getElements())
	{
		int type = 0;
		size_t size = 0;
		switch (element.type)
		{
		default:
		case VertexBufferElement::Type::Float:
		{
			type = GL_FLOAT;
			size = sizeof(float);
			break;
		}
		}

		glEnableVertexAttribArray(elementIndex);
		glVertexAttribPointer(
			elementIndex,
			// num of components
			element.size,
			type,
			element.normalized,
			// move forward size * sizeof(type) each iteration to get the next position
			layout.getStride() * size,
			// start at the beginning of the buffer
			(void*)(offset * size)
		);

		if (element.instanced)
		{
			glVertexAttribDivisor(elementIndex, 1);
		}

		offset += element.size;
		++elementIndex;
	}
}

void VertexBufferLayout::push(const VertexBufferElement& element)
{
	m_elements.push_back(element);
	m_stride += element.size;
}

void VertexBufferLayout::clear()
{
	m_elements.clear();
}
