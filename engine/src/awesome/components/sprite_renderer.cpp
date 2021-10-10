#include "sprite_renderer.h"

#include <awesome/editor/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/scene/entity.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, texture()
	, rect()
{

}

void SpriteRenderer::render(graphics::Renderer& renderer)
{
	if (texture != nullptr)
	{
		renderer.drawSprite(texture, getOwner()->transform.matrix(), rect);
	}
}

void SpriteRenderer::inspect(editor::Context& context)
{
	if (context.collapsingHeader("SpriteRenderer"))
	{
		context.input("enabled", &enabled);
		context.input("rect", &rect);
	}
}
