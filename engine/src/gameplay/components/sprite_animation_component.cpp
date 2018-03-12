#include <awesome/gameplay/components/sprite_animation_component.h>
#include <awesome/scenegraph/object.h>

namespace Awesome
{
	namespace Gameplay
	{
		void SpriteAnimationComponent::init()
		{
			sprite_rendering_component = owner()->findComponent<Rendering::SpriteRenderingComponent>();

			if (animations.size() > 0) {
				play(animations.begin()->first);
			}
		}

		void SpriteAnimationComponent::update(float delta_time)
		{
			if (animation != nullptr && !in_pause)
			{
				time += delta_time;
				
				if (time >= animation->frames[frame_index].frame_time)
				{
					sprite_rendering_component->crop(animation->frames[frame_index].frame_rect);
					time = 0;
					frame_index++;
					if (frame_index >= animation->frames.size())
						frame_index = 0;
				}
			}
		}

		void SpriteAnimationComponent::play()
		{
			in_pause = false;
		}

		void SpriteAnimationComponent::play(std::string animation_name)
		{
			for (auto it = animations.begin(); it != animations.end(); it++)
			{
				if (it->first == animation_name) {
					animation = &(it->second);
					stop();					
					break;
				}
			}

			play();
		}

		void SpriteAnimationComponent::pause()
		{
			in_pause = true;
		}

		void SpriteAnimationComponent::stop()
		{
			frame_index = 0;
			playing = true;
			in_pause = false;
			time = 0;

			if (animation != nullptr && sprite_rendering_component != nullptr)
			{
				sprite_rendering_component->crop(animation->frames[frame_index].frame_rect);
			}
		}
	}
}