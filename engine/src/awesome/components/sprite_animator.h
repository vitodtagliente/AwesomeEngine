/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>
#include <vector>

#include <awesome/entity/component.h>
#include <awesome/graphics/texture_rect.h>

class SpriteAnimator : public Component
{
public:

	struct Animation
	{
		struct Frame
		{
			Frame()
				: rect()
				, duration(0)
			{}

			Frame(const graphics::TextureRect& rect,  const double duration)
				: rect(rect)
				, duration(duration)
			{}

			graphics::TextureRect rect;
			double duration;
		};

		Animation()
			: startingFrame(0)
			, frames()
		{

		}

		unsigned int startingFrame;
		std::vector<Frame> frames;
	};

	SpriteAnimator();

	void update(double deltaTime) override;

	void play(const std::string& name, bool loop = false);
	void pause();
	void resume();
	void stop();

	inline bool isPlaying() const { return m_isPlaying; }

	std::map<std::string, Animation> animations;
	bool autoplay;

private:

	struct PlayingState
	{
		std::string name;
		Animation animation;
		unsigned int frameIndex;
		bool loop;
		double timeLeft;
	};

	void updateFrame(const Animation::Frame& frame);

	PlayingState m_state;
	bool m_isPlaying;
	class SpriteRenderer* m_spriteRenderer;
};