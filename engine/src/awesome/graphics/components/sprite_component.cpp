#include "sprite_component.h"

#include <awesome/graphics/graphics_api.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/renderable.h>
#include <awesome/graphics/mesh/quad.h>
#include <awesome/scene/object.h>

namespace awesome
{
	void SpriteComponent::push_data(Renderer* const t_renderer)
	{
		static Renderable* const quad_renderable = Renderer::instance()->getAPI()->createRenderable(Quad{});

		t_renderer->push(quad_renderable, material, getOwner()->transform.matrix());
	}
}