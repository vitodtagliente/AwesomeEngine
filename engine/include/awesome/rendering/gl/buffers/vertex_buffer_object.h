#pragma once

#include <dreamkeeper/core/buffer.h>
#include <glad/glad.h>

namespace Dreamkeeper 
{
	namespace Core
	{
		class VertexBufferObject : public Buffer 
		{
		public:
			VertexBufferObject() : Buffer(GL_ARRAY_BUFFER) { }
		};

		typedef VertexBufferObject VBO;
	}
}