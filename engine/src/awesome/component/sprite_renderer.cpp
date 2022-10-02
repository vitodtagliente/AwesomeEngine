#include "sprite_renderer.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

void SpriteRenderer::render(graphics::Renderer2D* const renderer)
{
	if (sprite && sprite->data.has_value())
	{
		const Sprite& data = sprite->data.value();
		if (data.image)
		{
			std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(data.image->descriptor.id);
			if (texture)
			{
				renderer->drawTexture(texture.get(), getOwner()->transform.matrix(), data.rect, color);
			}
		}
	}
}

void SpriteRenderer::update(const double /*deltaTime*/)
{
	math::vec3& scale = getOwner()->transform.scale;
	if ((flipX && scale.x > 0) || (!flipX && scale.x < 0))
	{
		scale.x = -scale.x;
	}
	if ((flipY && scale.y > 0) || (!flipY && scale.y < 0))
	{
		scale.y = -scale.y;
	}
}

json::value SpriteRenderer::serialize() const
{
	json::value data = Component::serialize();
	data["sprite"] = sprite ? ::serialize(sprite->descriptor.id) : "";
	data["color"] = ::serialize(color);
	data["flipX"] = flipX;
	data["flipY"] = flipY;
	return data;
}

void SpriteRenderer::deserialize(const json::value& value)
{
	Component::deserialize(value);

	uuid spriteId = uuid::Invalid;
	::deserialize(value["sprite"], spriteId);
	sprite = AssetLibrary::instance().find<SpriteAsset>(spriteId);
	::deserialize(value["color"], color);
	flipX = value.safeAt("flipX").as_bool(false);
	flipY = value.safeAt("flipY").as_bool(false);
}

void SpriteRenderer::inspect()
{
	Component::inspect();
	Layout::input("Sprite", sprite);
	Layout::input("Color", color);
	Layout::input("Flip X", flipX);
	Layout::input("Flip Y", flipY);
}