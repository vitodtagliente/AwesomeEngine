#pragma once

#include <cstddef>
#include "../types.h"

namespace awesome
{
	class IndexBuffer
	{
	public:

		IndexBuffer(const uint* t_data, const uint t_count);
		~IndexBuffer();

		void bind();
		void unbind();

		uint id() const;
		std::size_t size() const;
		uint count() const;

	private:

		// buffer id
		uint m_id;
		// buffer size
		std::size_t m_size;
		// num of elements
		uint m_count;
	};
}