#pragma once

#include "../types.h"

namespace awesome
{
	class VertexBuffer;
	class VertexBufferLayout;

	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

		uint id() const;

		void add(const VertexBuffer& t_buffer, const VertexBufferLayout& t_layout);

	private:

		// vertex array id
		uint m_id;

	};
}