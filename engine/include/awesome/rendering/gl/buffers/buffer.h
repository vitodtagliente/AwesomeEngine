#pragma once

#include <dreamkeeper/core/interfaces/base_buffer.h>
#include <glad/glad.h>

/*
These mentioned the mutable buffer maybe de-allocated or resized, and that comes from glBufferData which bring mutable buffer. 
But glBufferStorage will show you the ability to create immutable buffer
*/

namespace Dreamkeeper
{
	namespace Core
	{
		struct Buffer : public BaseBuffer
		{		
			unsigned int target;

			Buffer();
			Buffer(unsigned int target);
			
			void bind() override;
			void unbind() override;
			void free() override;
		
			/* allocate size and fill data */
			void allocate(unsigned int size, unsigned int flags = GL_STATIC_DRAW);
			void allocate(unsigned int size, const void* data, unsigned int flags = GL_STATIC_DRAW);
			/* fill a little range of buffer memory */
			void fill(unsigned int offset, unsigned int size, const void* data);
			/* retrieve the buffer's pointer */
			void* map(unsigned int usage = GL_WRITE_ONLY);
			/* retrieve the pointer to a little range of buffer memory */
			void* mapRange(unsigned int offset, unsigned int length, unsigned int access = GL_MAP_WRITE_BIT);
			/* unmap the buffer*/
			void unmap();
		};
	}
}