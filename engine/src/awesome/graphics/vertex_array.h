#pragma once

#include "../types.h"

namespace awesome
{
	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

		uint id() const;

	private:

		// vertex array id
		uint m_id;

	};
}