#pragma once

#include "graphics_element.h"

namespace awesome
{
	class VertexBuffer;
	class VertexBufferLayout;

	class VertexArray : public IGraphicsElement
	{
	public:

		void add(const VertexBuffer& t_buffer, const VertexBufferLayout& t_layout);
	};
}