#include "vertex_buffer_layout.h"
#include <glad/glad.h>

namespace awesome
{
	VertexBufferElement::VertexBufferElement(const uint t_count, const uint t_type, const std::size_t t_size, const bool t_normalized)
		: count(t_count)
		, type(t_type)
		, normalized(t_normalized)
	{
		size = t_count * t_size;
	}

	const uint VertexBufferLayout::float_t = GL_FLOAT;
	const uint VertexBufferLayout::uint_t = GL_UNSIGNED_INT;
	const uint VertexBufferLayout::ubyte_t = GL_UNSIGNED_BYTE;

	VertexBufferLayout::VertexBufferLayout()
		: m_elements()
		, m_stride(0)
	{

	}
	
	std::size_t VertexBufferLayout::getStride() const
	{
		return m_stride;
	}

	const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
	{
		return m_elements;
	}
}