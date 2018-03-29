#include <awesome/rendering/components/sprite_rendering_component.h>
#include <awesome/rendering/sprite_batch.h>

namespace Awesome
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