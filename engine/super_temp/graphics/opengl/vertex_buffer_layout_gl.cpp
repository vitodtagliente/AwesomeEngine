#include "vertex_buffer_layout_gl.h"

#include "opengl.h"

namespace awesome
{
	VertexBufferLayoutGL::VertexBufferLayoutGL()
		: VertexBufferLayout()
	{
		float_t = GL_FLOAT;
		uint_t = GL_UNSIGNED_INT;
		ubyte_t = GL_UNSIGNED_BYTE;
	}
}