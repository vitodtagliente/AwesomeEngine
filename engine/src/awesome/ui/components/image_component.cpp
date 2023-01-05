#include "image_component.h"

#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

void ImageComponent::render(graphics::Renderer2D* const renderer)
{
	if (image == nullptr || image->state != Asset::State::Ready) return;

	std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image->descriptor.id);
	if (texture)
	{
		renderer->drawTexture(texture.get(), getOwner()->transform.matrix(), rect, color);
	}
}

void ImageComponent::update(const double /*deltaTime*/)
{

}