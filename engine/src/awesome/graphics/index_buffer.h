#pragma once

#include <cstddef>
#include "../core/types.h"
#include "graphics_element.h"

namespace awesome
{
	class IndexBuffer : public IGraphicsElement
	{
	public:

		IndexBuffer(const uint * const t_data, const uint t_count)
			: m_count(t_count)
		{

		}

		inline std::size_t size() const { return m_size; }
		inline uint count() const { return m_count; }

	protected:

		// buffer size
		std::size_t m_size;
		// num of elementa
		uint m_count;
	};
}