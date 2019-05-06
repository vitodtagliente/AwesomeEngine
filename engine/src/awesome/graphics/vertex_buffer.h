#pragma once

#include <cstddef>
#include "graphics_element.h"

namespace awesome
{
	class VertexBuffer : public IGraphicsElement
	{
	public:

		enum class AccessMode
		{
			StaticDraw
		};

		VertexBuffer(const void* const t_data, const std::size_t t_size, const AccessMode t_mode = AccessMode::StaticDraw);

		inline std::size_t size() const { return m_size; }

	protected:

		// buffer size
		std::size_t m_size;
	};
}