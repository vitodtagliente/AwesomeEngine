/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <optional>
#include <string>

#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/scene/component.h>

#include "sprite_animator_component_generated.h"

CLASS(Type = Component)
class SpriteAnimatorComponent : public Component
{
public:
	SpriteAnimatorComponent() = default;
	virtual ~SpriteAnimatorComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	void play(const std::string& name, bool loop = false);
	void pause();
	void resume();
	void stop();

	inline bool isPlaying() const { return m_isPlaying; }
	std::optional<std::string> getPlayingAnimation() const;

	PROPERTY() std::map<std::string, SpriteAnimationAsset> animations;
	PROPERTY() bool autoplay{ true };

	GENERATED_BODY()

private:
	struct PlayingState
	{
		std::string animation;
		unsigned int frameIndex{ 0 };
		bool loop{ false };
		double timeLeft{ 0.0 };
	};

	void updateFrame(const SpriteAnimationFrame& frame);

	PlayingState m_state;
	bool m_isPlaying{ false };
	class SpriteRendererComponent* m_spriteRenderer{ nullptr };
};