#include "sprite_renderer.h"

#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, sprite()
	, color(graphics::Color::White)
{

}

void SpriteRenderer::render(graphics::Renderer* const renderer)
{
	if (sprite.image != nullptr)
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance()->find(sprite.image->id);
		if (texture)
		{
			renderer->drawSprite(texture.get(), getOwner()->transform.matrix(), sprite.rect);
		}
	}
}

json::value SpriteRenderer::serialize() const
{
	json::value data = Component::serialize();
	data.insert("color", ::serialize(color));
	return data;
}

void SpriteRenderer::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("Color", &color);
}

REFLECT_IMP(SpriteRenderer)