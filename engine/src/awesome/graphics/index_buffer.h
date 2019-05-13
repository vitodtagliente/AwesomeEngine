#pragma once

#include <cstddef>
#include "graphics_buffer.h"

namespace awesome
{
	class IndexBuffer : public GraphicsBuffer
	{
	public:

		IndexBuffer(const unsigned int * const t_data, const unsigned int t_count)
			: m_size()
			, m_count(t_count)
		{

		}

		inline std::size_t size() const { return m_size; }
		inline unsigned int count() const { return m_count; }

	protected:

		// buffer size
		std::size_t m_size;
		// num of elements
		unsigned int m_count;
	};
}