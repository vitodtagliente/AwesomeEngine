#include "sprite_renderer_component.h"

#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

void SpriteRendererComponent::render(graphics::Renderer& renderer)
{
	if (!image.ready())
	{
		image.load();
		return;
	}
	
	std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image);
	if (texture != nullptr)
	{
		renderer.submitDrawTexture(texture.get(), getOwnerTransform().matrix(), rect, color);
	}
}

void SpriteRendererComponent::update(const double /*deltaTime*/)
{
	math::vec3& scale = getOwnerTransform().scale;
	if ((flipX && scale.x > 0) || (!flipX && scale.x < 0))
	{
		scale.x = -scale.x;
	}
	if ((flipY && scale.y > 0) || (!flipY && scale.y < 0))
	{
		scale.y = -scale.y;
	}
}
