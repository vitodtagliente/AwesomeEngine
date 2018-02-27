#include <awesome/rendering/components/sprite_rendering_component.h>
#include <awesome/rendering/shading/texture.h>
#include <awesome/rendering/primitives/primitives.h>

namespace Awesome
{
	namespace Rendering
	{
		void SpriteRenderingComponent::init()
		{
			mesh = Primitive::generate<Square>();
			if (cropTexture)
			{
				
			}
			MeshRenderingComponent::init();
		}

		void SpriteRenderingComponent::update(float delta_time)
		{

		}

		void SpriteRenderingComponent::render()
		{
			texture->bind();
			MeshRenderingComponent::render();
		}
	}
}