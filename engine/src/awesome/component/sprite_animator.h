/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>
#include <vector>

#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/core/serialization.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/texture_rect.h>

namespace component
{
	class SpriteAnimator : public Component
	{
	public:

		SpriteAnimator();

		void update(double deltaTime) override;

		void play(const std::string& name, bool loop = false);
		void pause();
		void resume();
		void stop();

		inline bool isPlaying() const { return m_isPlaying; }
		std::string getPlayingAnimation() const;

		std::map<std::string, SpriteAnimationAssetPtr> animations;
		bool autoplay;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		REFLECT()

	private:

		struct PlayingState
		{
			std::string name;
			SpriteAnimationAssetPtr animation;
			unsigned int frameIndex;
			bool loop;
			double timeLeft;
		};

		void updateFrame(const SpriteAnimation::Frame& frame);

		PlayingState m_state;
		bool m_isPlaying;
		class SpriteRenderer* m_spriteRenderer;
	};
}