#include "sprite_renderer.h"

#include <awesome/data/asset_library.h>
#include <awesome/data/sprite_asset.h>
#include <awesome/editor/layout.h>
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
	if (sprite && sprite->data.image)
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance()->find(sprite->data.image->id);
		if (texture)
		{
			renderer->drawSprite(texture.get(), getOwner()->transform.matrix(), sprite->data.rect);
		}
	}
}

json::value SpriteRenderer::serialize() const
{
	json::value data = Component::serialize();
	data.insert("sprite", sprite ? ::serialize(sprite->id) : "");
	data.insert("color", ::serialize(color));
	return data;
}

void SpriteRenderer::deserialize(const json::value& value)
{
	Component::deserialize(value);

	uuid spriteId = uuid::Invalid;
	::deserialize(value["sprite"], spriteId);
	sprite = AssetLibrary::instance()->find<SpriteAsset>(spriteId);
	::deserialize(value["color"], color);
}

void SpriteRenderer::inspect()
{
	Component::inspect();
	editor::Layout::input("Sprite", sprite);
	editor::Layout::input("Color", color);
}

REFLECT_COMPONENT(SpriteRenderer)