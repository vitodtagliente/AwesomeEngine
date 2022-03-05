/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "buffer.h"

namespace graphics
{
	enum class IndexFormat
	{
		UInt32,
		UInt16,
		UInt8
	};

	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(size_t size, BufferUsageMode mode = BufferUsageMode::Static);
		virtual ~IndexBuffer() override;

		virtual void bind() override;
		virtual void unbind() override;
		virtual void free() override;
		virtual void fillData(void* const data, size_t size) override;
		virtual void fillSubData(void* const data, size_t size, int offset) override;

	private:
		unsigned int m_id;
	};
}