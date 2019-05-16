#include "graphics_buffer.h"

namespace awesome
{
	GraphicsBufferElement::GraphicsBufferElement(
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

	GraphicsBufferLayout::GraphicsBufferLayout()
		: m_elements()
		, m_stride(0)
	{

	}

	void GraphicsBufferLayout::push(const GraphicsBufferElement& t_element)
	{
		m_elements.push_back(t_element);
		m_stride += t_element.size;
	}

	void GraphicsBufferLayout::clear()
	{
		m_elements.clear();
	}

	GraphicsBuffer::GraphicsBuffer(const Type t_type, const void * const t_data, const std::size_t t_size)
		: layout()
		, m_type(t_type)
		, m_size(t_size)
	{
	}

	GraphicsBuffer::~GraphicsBuffer()
	{
	}
}