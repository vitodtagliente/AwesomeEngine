#pragma once

#include "../index_buffer.h"

namespace awesome
{
	class IndexBufferGL final : public IndexBuffer
	{
	public:

		IndexBufferGL(const uint * const t_data, const uint t_count);
		~IndexBufferGL();

		virtual void bind() override;
		virtual void unbind() override;
	};
}