#include <awesome/rendering/rendering_data.h>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
	{
		void RenderingData::bind()
		{
			glBindVertexArray(vao);
		}

		void RenderingData::unbind()
		{
			glBindVertexArray(0);
		}
	}
}