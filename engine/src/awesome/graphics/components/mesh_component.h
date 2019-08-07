#pragma once

#include "rendering_component.h"

namespace awesome
{
	struct Mesh;
	class Renderable;

	class MeshComponent : public RenderingComponent
	{
	public:

		virtual void push_data(Renderer* const t_renderer) override;

		// mesh to be rendered
		Mesh* mesh;

	private:

		Renderable* m_renderable{ nullptr };
	};
}