#pragma once

namespace awesome
{
	class GraphicsBuffer;

	class Renderable
	{
	public:

		Renderable(GraphicsBuffer* const t_vertex, GraphicsBuffer* const t_index);
		virtual ~Renderable();

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}