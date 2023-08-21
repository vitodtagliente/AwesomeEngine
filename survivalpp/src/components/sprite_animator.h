/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

#include "asset/sprite_animation.h"

#include "ecs/component.h"
#include "ecs/component_ptr.h"

#include "sprite.h"

struct SpriteAnimation;

class SpriteAnimator : public Component
{
public:
	void play(const std::string& name);
	void pause();
	void resume();
	void stop();

	const SpriteAnimationFrame& frame() const;

	inline bool isPlaying() const { return m_isPlaying; }

	virtual void init() override;
	void update(double delta_time);

	std::map<std::string, SpriteAnimation> animations;
	bool autoplay{ true };
	std::string autoplay_animation;

private:
	struct PlayingState
	{
		std::string animation;
		unsigned int frameIndex{ 0 };
		bool loop{ false };
		double timeLeft{ 0.0 };
	};

	bool m_isPlaying{ false };
	ComponentPtr<Sprite> m_sprite;
	PlayingState m_state;
};