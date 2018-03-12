#pragma once

#include <map>
#include <string>
#include <vector>
#include "../../scenegraph/component.h"
#include "../../rendering/components/sprite_rendering_component.h"
#include "../../math/rect.h"
#include "../../rendering/shading/texture.h"

namespace Awesome
{
	namespace Gameplay
	{
		struct SpriteAnimationData
		{
			Rendering::Texture* texture{ nullptr };
			Math::Rect frame_rect{ 0.0f,0.0f,1.0f,1.0f };
			float frame_time{ 0.5f };
		};

		struct SpriteAnimation
		{
			std::vector<SpriteAnimationData> frames;
		};

		class SpriteAnimationComponent : public Scenegraph::Component
		{
		private:
			float time{ 0.0f };
			int frame_index{ 0 };
			bool in_pause{ false };
			bool playing{ false };
			Rendering::SpriteRenderingComponent* sprite_rendering_component{ nullptr };

		public:
			std::map<std::string, SpriteAnimation> animations;
			SpriteAnimation* animation{ nullptr };

			void play();
			void play(std::string animation_name);
			void pause();
			void stop();

			void init() override;
			void update(float delta_time) override;
		};
	}
}