#include "index_buffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(size_t size, BufferUsageMode mode)
	: Buffer(size, mode)
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
		GL_ELEMENT_ARRAY_BUFFER,
		size,
		nullptr,
		usage
	);
}

IndexBuffer::~IndexBuffer()
{
	free();
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::free()
{
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::fillData(void* const data, size_t size)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

void IndexBuffer::fillSubData(void* const data, size_t size, int offset)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
