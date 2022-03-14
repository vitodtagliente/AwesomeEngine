#include "sprite_renderer.h"

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
		renderer->drawSprite(texture.get(), getOwner()->transform.matrix(), rect);
	}
}
