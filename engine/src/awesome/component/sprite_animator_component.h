/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>
#include <vector>

#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/texture_rect.h>

#include "sprite_animator_component_generated.h"

CLASS(Category = Component)
class SpriteAnimatorComponent : public Component
{
public:
	SpriteAnimatorComponent();

	void update(double deltaTime) override;

	void play(const std::string& name, bool loop = false);
	void pause();
	void resume();
	void stop();

	inline bool isPlaying() const { return m_isPlaying; }
	std::string getPlayingAnimation() const;

	PROPERTY() std::map<std::string, SpriteAnimationAssetPtr> animations;
	PROPERTY() bool autoplay;

	GENERATED_BODY()

private:

	struct PlayingState
	{
		std::string name;
		SpriteAnimationAssetPtr animation;
		unsigned int frameIndex{ 0 };
		bool loop{ false };
		double timeLeft{ 0.0 };
	};

	void updateFrame(const SpriteAnimationFrame& frame);

	PlayingState m_state;
	bool m_isPlaying;
	class SpriteRendererComponent* m_spriteRenderer;
};