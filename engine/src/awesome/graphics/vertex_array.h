#pragma once

#include "graphics_element.h"

namespace awesome
{
	class VertexBuffer;
	class VertexBufferLayout;

	class VertexArray : public IGraphicsElement
	{
	public:

		virtual void add(VertexBuffer* const t_buffer, VertexBufferLayout* const t_layout) = 0;
	};
}