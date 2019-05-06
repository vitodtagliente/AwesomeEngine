#pragma once

#include "../vertex_buffer.h"

namespace awesome
{
	class VertexBufferGL final : public VertexBuffer
	{
	public:

		VertexBufferGL(const void* const t_data, const std::size_t t_size, const AccessMode t_mode = AccessMode::StaticDraw);
		~VertexBufferGL();

		virtual void bind() override;
		virtual void unbind() override;
	};
}