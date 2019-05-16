#pragma once

#include "../renderable.h"

namespace awesome
{
	class RenderableGL final : public Renderable
	{
	public:

		RenderableGL(GraphicsBuffer* const t_vertex, GraphicsBuffer* const t_index);
		virtual ~RenderableGL() override;

		inline unsigned int id() const { return m_id; }

		virtual void bind() override;
		virtual void unbind() override;

	private:

		// id
		unsigned int m_id;
	};
}