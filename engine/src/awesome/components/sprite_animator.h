/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>
#include <vector>

#include <awesome/core/serialization.h>
#include <awesome/data/sprite.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/texture_rect.h>

class SpriteAnimator : public Component
{
public:

	struct Animation : public ISerializable
	{
		struct Frame : public ISerializable
		{
			Frame()
				: sprite()
				, duration(0)
			{}

			Frame(const Sprite& sprite,  const double duration)
				: sprite(sprite)
				, duration(duration)
			{}

			virtual json::value serialize() const override;
			virtual void deserialize(const json::value& value) override;

			Sprite sprite;
			double duration;
		};

		Animation()
			: startingFrame(0)
			, frames()
		{

		}

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;

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

	virtual json::value serialize() const override;
	virtual void inspect() override;

	REFLECT()

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