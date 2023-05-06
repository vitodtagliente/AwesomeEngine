#include "sprite_animator_component.h"

#include <awesome/scene/entity.h>
#include "sprite_renderer_component.h"

void SpriteAnimatorComponent::init()
{
	if (autoplay && !animations.empty())
	{
		play(animations.begin()->first, true);
	}
}

void SpriteAnimatorComponent::update(const double deltaTime)
{
	if (!m_isPlaying) return;

	m_state.timeLeft -= deltaTime;
	if (m_state.timeLeft <= 0)
	{
		const SpriteAnimation& animation = *animations[m_state.animation].resource;
		++m_state.frameIndex;
		if (m_state.frameIndex >= animation.frames.size())
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

		if (m_state.frameIndex < animation.frames.size())
		{
			const auto& frame = animation.frames[m_state.frameIndex];
			m_state.timeLeft = frame.duration;
			updateFrame(frame);
		}
	}
}

void SpriteAnimatorComponent::play(const std::string& name, const bool loop)
{
	if (m_isPlaying && m_state.animation == name)
	{
		// already playing the selected animation
		return;
	}

	const auto& it = animations.find(name);
	if (it == animations.end()) return;

	const SpriteAnimationAsset& animation = it->second;
	if (!animation.ready()) return;

	m_state.animation = name;
	m_state.frameIndex = animation.resource->startingFrame;
	m_state.loop = loop;

	const auto& frames = animation.resource->frames;
	if (m_state.frameIndex < frames.size())
	{
		const auto& frame = frames[m_state.frameIndex];
		m_state.timeLeft = frame.duration;
		updateFrame(frame);
	}

	m_isPlaying = true;
}

void SpriteAnimatorComponent::pause()
{
	m_isPlaying = false;
}

void SpriteAnimatorComponent::resume()
{
	m_isPlaying = true;
}

void SpriteAnimatorComponent::stop()
{
	m_isPlaying = false;
	m_state.frameIndex = 0;
}

std::optional<std::string> SpriteAnimatorComponent::getPlayingAnimation() const
{
	if (m_isPlaying)
	{
		return m_state.animation;
	}
	return std::nullopt;
}

void SpriteAnimatorComponent::updateFrame(const SpriteAnimationFrame& frame)
{
	if (m_spriteRenderer == nullptr)
	{
		m_spriteRenderer = getOwner()->findComponent<SpriteRendererComponent>();
	}

	if (m_spriteRenderer)
	{
		m_spriteRenderer->rect = frame.rect;
	}
}