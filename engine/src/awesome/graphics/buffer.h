/// Copyright (c) Vito Domenico Tagliente
#pragma once

namespace graphics
{
	enum class BufferUsageMode
	{
		Static,
		Dynamic,
		Stream
	};

	class Buffer
	{
	public:
		Buffer(size_t size, BufferUsageMode mode = BufferUsageMode::Static);
		virtual ~Buffer() = default;

		inline size_t size() const { return m_size; }
		inline BufferUsageMode mode() const { return m_mode; }

		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void free() = 0;
		virtual void fillData(void* const data, size_t size) = 0;
		virtual void fillSubData(void* const data, size_t size, int offset) = 0;

	private:
		size_t m_size;
		BufferUsageMode m_mode;
	};
}