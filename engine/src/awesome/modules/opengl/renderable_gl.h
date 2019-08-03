#pragma once

#include <awesome/graphics/renderable.h>

namespace awesome
{
	class RenderableGL final : public Renderable
	{
	public:

		RenderableGL();
		RenderableGL(const Mesh& t_mesh);
		virtual ~RenderableGL() override;

		virtual void bind() override;
		virtual void unbind() override;

	private:

		// vertex array object
		unsigned int m_vao;
		// vertex buffer object
		unsigned int m_vbo;
		// elements buffer object
		unsigned int m_ebo;
	};
}