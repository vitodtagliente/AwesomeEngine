#include "sprite_renderer.h"

#include <awesome/editor/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/entity/entity.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, texture()
	, rect()
{

}

void SpriteRenderer::render(graphics::Renderer* const renderer)
{
	if (texture != nullptr)
	{
		renderer->drawSprite(texture, getOwner()->transform.matrix(), rect);
	}
}

void SpriteRenderer::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("rect", &rect);
}
