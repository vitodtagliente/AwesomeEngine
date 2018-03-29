#pragma once

#include <map>
#include <string>
#include <vector>
#include "../../component.h"
#include "../../rendering/components/sprite_rendering_component.h"
#include "../../math/rect.h"
#include "../../rendering/shading/texture.h"

namespace Awesome
{
	struct SpriteAnimationData
	{
		Texture* texture{ nullptr };
		Rect frame_rect{ 0.0f,0.0f,1.0f,1.0f };
		float frame_time{ 0.5f };

		SpriteAnimationData()
		{

		}

		SpriteAnimationData(Texture* in_texture, const Rect& rect, const float time)
		{
			texture = in_texture;
			frame_rect = rect;
			frame_time = time;
		}
	};

	struct SpriteAnimation
	{
		std::vector<SpriteAnimationData> frames;
	};

	class SpriteAnimationComponent : public Component
	{
	private:
		float time{ 0.0f };
		int frame_index{ 0 };
		bool in_pause{ false };
		bool playing{ false };
		SpriteRenderingComponent* sprite_rendering_component{ nullptr };

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