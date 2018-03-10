#include <awesome/rendering/components/sprite_rendering_component.h>
#include <awesome/rendering/shading/texture.h>
#include <awesome/rendering/primitives/primitives.h>
#include <awesome/rendering/sprite_batch.h>
#include <awesome/scenegraph/object.h>

#include <glad/glad.h>
#include <vector>

namespace Awesome
{
	namespace Rendering
	{
		void SpriteRenderingComponent::init()
		{
			
		}

		void SpriteRenderingComponent::crop(const Math::Rect& crop)
		{
			if (textureCoords != crop)
			{
				textureCoords = crop;
			}
		}

		void SpriteRenderingComponent::update(float delta_time)
		{

		}

		void SpriteRenderingComponent::render()
		{
			auto sprite_batch = SpriteBatch::instance();
			if (sprite_batch != nullptr)
			{
				SpriteBatchRenderingData data;
				data.material = material;
				data.textureCoords = textureCoords;
				data.transform = owner()->transform.get();
				sprite_batch->add(texture, data);
			}
		}
	}
}