#include "mesh_component.h"

#include <awesome/graphics/graphics_api.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/renderable.h>
#include <awesome/engine/object.h>

namespace awesome
{
	void MeshComponent::push_data(Renderer* const t_renderer)
	{
		if (m_renderable == nullptr)
		{
			m_renderable = t_renderer->getAPI()->createRenderable(*mesh);
		}

		t_renderer->push(m_renderable, material, getOwner()->transform.matrix());
	}
}