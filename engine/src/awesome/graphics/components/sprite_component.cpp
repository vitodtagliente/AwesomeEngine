#include "sprite_component.h"

#include "../renderer.h"
#include "../texture.h"
#include "../renderable.h"
#include "../graphics_module.h"
#include "../mesh/quad.h"
#include "../../scene/object.h"

namespace awesome
{
	void SpriteComponent::push_data(Renderer* const t_renderer)
	{
		static Renderable* const quad_renderable = GraphicsModule::instance()->createRenderable(Quad{});

		t_renderer->push(quad_renderable, material, getOwner()->transform.matrix());
	}
}