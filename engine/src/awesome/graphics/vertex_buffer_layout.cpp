#include "vertex_buffer_layout.h"

namespace awesome
{
	VertexBufferElement::VertexBufferElement(const uint t_count, const uint t_type, const std::size_t t_size, const bool t_normalized)
		: count(t_count)
		, type(t_type)
		, size(t_size)
	{
		normalized = t_count * t_size;
	}

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