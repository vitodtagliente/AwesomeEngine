#include "sprite_animator.h"

#include "ecs/entity.h"
#include "engine/time.h"

void SpriteAnimator::play(const std::string& name)
{
	if (m_isPlaying && m_state.animation == name)
	{
		// already playing the selected animation
		return;
	}

	const auto& it = animations.find(name);
	if (it == animations.end()) return;

	const SpriteAnimation& animation = it->second;

	m_state.animation = name;
	m_state.frameIndex = animation.startingFrame;
	m_state.loop = animation.loop;

	const auto& frames = animation.frames;
	if (m_state.frameIndex < frames.size())
	{
		const auto& frame = frames[m_state.frameIndex];
		m_state.timeLeft = frame.duration;
	}

	m_isPlaying = true;
}

void SpriteAnimator::pause()
{
	m_isPlaying = false;
}

void SpriteAnimator::resume()
{
	m_isPlaying = true;
}

void SpriteAnimator::stop()
{
	m_isPlaying = false;
	m_state.frameIndex = 0;
}

void SpriteAnimator::init()
{
	m_sprite = entity()->findComponent<Sprite>();
	
	if (autoplay && !animations.empty())
	{
		if (autoplay_animation.empty())
			play(animations.begin()->first);
		else 
			play(autoplay_animation);
	}
}

void SpriteAnimator::update(const double delta_time)
{
	if (!m_isPlaying) return;

	m_state.timeLeft -= delta_time;
	if (m_state.timeLeft <= 0)
	{
		const SpriteAnimation& animation = animations[m_state.animation];
		++m_state.frameIndex;
		if (m_state.frameIndex >= animation.frames.size())
		{
			if (m_state.loop)
			{
				m_state.frameIndex = 0;
			}
			else
			{
				--m_state.frameIndex;
				m_isPlaying = false;
			}
		}

		if (m_state.frameIndex < animation.frames.size())
		{
			const auto& frame = animation.frames[m_state.frameIndex];
			m_state.timeLeft = frame.duration;
		}

		if (m_sprite)
		{
			m_sprite->rect = frame().rect;
		}
	}
}

const SpriteAnimationFrame& SpriteAnimator::frame() const
{
	const SpriteAnimation& animation = animations.at(m_state.animation);
	return animation.frames[m_state.frameIndex];
}