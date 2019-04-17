#pragma once

#include <cstddef>
#include "../types.h"

namespace awesome
{
	class VertexBuffer final
	{
	public:

		enum class AccessMode
		{
			StaticDraw
		};

		VertexBuffer(const void* t_data, const std::size_t t_size, const AccessMode t_access = AccessMode::StaticDraw);
		~VertexBuffer();

		void bind();
		void unbind();

		uint getId() const;

	private:

		// buffer id
		uint m_id;
		// buffer size
		std::size_t m_size;
	};
}