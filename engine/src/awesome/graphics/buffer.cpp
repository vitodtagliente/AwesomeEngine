#include "buffer.h"

namespace graphics
{
	Buffer::Buffer(const size_t size, const BufferUsageMode mode)
		: m_size(size)
		, m_mode(mode)
	{
	}
}