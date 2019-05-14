#pragma once

#include "graphics_buffer.h"

namespace awesome
{
	class VertexBuffer;
	class VertexBufferLayout;

	class VertexArray : public GraphicsBuffer
	{
	public:

		virtual void add(VertexBuffer* const t_buffer, VertexBufferLayout* const t_layout) = 0;
	};
}