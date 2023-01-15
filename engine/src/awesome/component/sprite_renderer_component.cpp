#include "sprite_renderer_component.h"

#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

void SpriteRendererComponent::render(graphics::Renderer2D* const renderer)
{
	if (image == nullptr || image->state != Asset::State::Ready)
	{
		return;
	}
	
	std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image->id);
	if (texture != nullptr)
	{
		renderer->drawTexture(texture.get(), getOwner()->transform.matrix(), rect, color);
	}
}

void SpriteRendererComponent::update(const double /*deltaTime*/)
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