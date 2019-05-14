#pragma once

#include "../index_buffer.h"

namespace awesome
{
	class IndexBufferGL final : public IndexBuffer
	{
	public:

		IndexBufferGL(const unsigned int * const t_data, const unsigned int t_count);
		~IndexBufferGL();

		virtual void bind() override;
		virtual void unbind() override;
	};
}