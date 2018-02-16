#pragma once

namespace Awesome
{
	namespace Rendering
	{
		struct RenderingData
		{
			/* Vertex Array Object */
			unsigned int vao{ 0 };
			/* Vertex Buffer Object */
			unsigned int vbo{ 0 };
			/* Element Buffer Object */
			unsigned int ebo{ 0 };
			/* Element Array Buffer */
			unsigned int eab{ 0 };

			void bind();
			void unbind();
		};
	}
}