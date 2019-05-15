#include "vertex_buffer_layout.h"

namespace awesome
{
	VertexBufferElement::VertexBufferElement(
		const unsigned int t_count, 
		const Type t_type, 
		const std::size_t t_size, 
		const bool t_normalized
	)
		: count(t_count)
		, type(t_type)
		, normalized(t_normalized)
	{
		size = t_count * t_size;
	}


	VertexBufferLayout::VertexBufferLayout()
		: m_elements()
		, m_stride(0)
	{

	}

	void VertexBufferLayout::push(const VertexBufferElement& t_element)
	{
		m_elements.push_back(t_element);
		m_stride += t_element.size;
	}
}