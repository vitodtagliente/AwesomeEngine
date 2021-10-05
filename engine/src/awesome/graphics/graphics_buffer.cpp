#include "graphics_buffer.h"

#include <glad/glad.h>

GraphicsBufferElement::GraphicsBufferElement(
	const unsigned int count,
	const Type type,
	const std::size_t t_size,
	const bool normalized
)
	: count(count)
	, type(type)
	, normalized(normalized)
{
	size = count * t_size;
}

GraphicsBufferLayout::GraphicsBufferLayout()
	: m_elements()
	, m_stride(0)
{

}

void GraphicsBufferLayout::push(const GraphicsBufferElement& element)
{
	m_elements.push_back(element);
	m_stride += element.size;
}

void GraphicsBufferLayout::clear()
{
	m_elements.clear();
}

GraphicsBuffer::GraphicsBuffer(const Type type, const void* const data, const std::size_t size)
	: layout()
	, m_id()
	, m_nativeType()
	, m_type(type)
	, m_size(size)
{
	glGenBuffers(1, &m_id);

	switch (type)
	{
	case GraphicsBuffer::Type::Index:
		m_nativeType = GL_ELEMENT_ARRAY_BUFFER;
		break;
	default:
	case GraphicsBuffer::Type::Vertex:
		m_nativeType = GL_ARRAY_BUFFER;
		break;
	}

	bind();
	glBufferData(m_nativeType, size, data, GL_STATIC_DRAW);
}

GraphicsBuffer::~GraphicsBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void GraphicsBuffer::bind()
{
	glBindBuffer(m_nativeType, m_id);
}

void GraphicsBuffer::unbind()
{
	glBindBuffer(m_nativeType, 0);
}
