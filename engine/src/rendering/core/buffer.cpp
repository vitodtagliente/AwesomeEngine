#include <dreamkeeper/core/buffer.h>
#include <glad/glad.h>

namespace Dreamkeeper
{
	namespace Core
	{

		Buffer::Buffer()
		{

		}

		Buffer::Buffer(unsigned int target)
		{
			this->target = target;
		}
		
		void Buffer::bind()
		{
			if (id == 0)
				glGenBuffers(1, &id);
			glBindBuffer(target, id);
		}

		void Buffer::unbind()
		{
			glBindBuffer(target, 0);
		}

		void Buffer::free()
		{
			glDeleteBuffers(1, &id);
		}

		void Buffer::allocate(unsigned int size, unsigned int flags /*= GL_STATIC_DRAW*/)
		{
			glBufferData(target, size, nullptr, flags);
		}

		void Buffer::allocate(unsigned int size, const void* data, unsigned int flags /*= GL_STATIC_DRAW*/)
		{
			glBufferData(target, size, data, flags);
		}

		void Buffer::fill(unsigned int offset, unsigned int size, const void* data)
		{
			glBufferSubData(target, offset, size, data);
		}
		
		void* Buffer::map(unsigned int usage /*= GL_WRITE_ONLY*/)
		{
			return glMapBuffer(target, usage);
		}

		void* Buffer::mapRange(unsigned int offset, unsigned int length, unsigned int access /*= GL_MAP_WRITE_BIT*/)
		{
			return glMapBufferRange(target, offset, length, access);
		}

		void Buffer::unmap()
		{
			glUnmapBuffer(target);
		}
	}
}