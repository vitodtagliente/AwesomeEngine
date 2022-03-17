#include "sprite_animator.h"

#include <awesome/entity/entity.h>

#include "sprite_renderer.h"

SpriteAnimator::SpriteAnimator()
	: Component()
	, animations()
	, autoplay()
	, m_state()
	, m_isPlaying()
	, m_spriteRenderer()
{
}

void SpriteAnimator::update(const double deltaTime)
{
	if (m_isPlaying)
	{
		m_state.timeLeft -= deltaTime;
		if (m_state.timeLeft <= 0)
		{
			++m_state.frameIndex;
			if (m_state.frameIndex >= m_state.animation.frames.size())
			{
				if (m_state.loop)
				{
					m_state.frameIndex = 0;					
				}
				else
				{
					m_isPlaying = false;
					return;
				}
			}

			if (m_state.frameIndex < m_state.animation.frames.size())
			{
				const Animation::Frame& frame = m_state.animation.frames[m_state.frameIndex];
				m_state.timeLeft = frame.duration;
				updateFrame(frame);
			}
		}
	}
	else
	{
		if (autoplay && !animations.empty())
		{
			play(animations.begin()->first, true);
		}
	}
}

void SpriteAnimator::play(const std::string& name, const bool loop)
{
	if (m_isPlaying && m_state.name == name)
	{
		// already playing the selected animation
		return;
	}

	const auto& it = animations.find(name);
	if (it == animations.end()) return;

	m_state.name = name;
	m_state.animation = it->second;
	m_state.frameIndex = m_state.animation.startingFrame;
	m_state.loop = loop;

	if (m_state.frameIndex < m_state.animation.frames.size())
	{
		const Animation::Frame& frame = m_state.animation.frames[m_state.frameIndex];
		m_state.timeLeft = frame.duration;
		updateFrame(frame);
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

void SpriteAnimator::updateFrame(const Animation::Frame& frame)
{
	if (m_spriteRenderer == nullptr)
	{
		m_spriteRenderer = getOwner()->findComponent<SpriteRenderer>();
	}

	if (m_spriteRenderer)
	{
		m_spriteRenderer->sprite = frame.sprite;
	}
}
