#include "sprite_animator_component.h"

#include <awesome/asset/asset_library.h>
#include <awesome/entity/entity.h>

#include "sprite_renderer_component.h"

SpriteAnimatorComponent::SpriteAnimatorComponent()
	: Component()
	, animations()
	, autoplay()
	, m_state()
	, m_isPlaying()
	, m_spriteRenderer()
{
}

void SpriteAnimatorComponent::update(const double deltaTime)
{
	if (m_isPlaying)
	{
		m_state.timeLeft -= deltaTime;
		if (m_state.timeLeft <= 0)
		{
			const SpriteAnimation& animation = m_state.animation->data.value();
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
				const SpriteAnimation::Frame& frame = animation.frames[m_state.frameIndex];
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

void SpriteAnimatorComponent::play(const std::string& name, const bool loop)
{
	if (m_isPlaying && m_state.name == name)
	{
		// already playing the selected animation
		return;
	}

	const auto& it = animations.find(name);
	if (it == animations.end()) return;
	if (!it->second->data.has_value()) return;

	const SpriteAnimation& animation = it->second->data.value();

	m_state.name = name;
	m_state.animation = it->second;
	m_state.frameIndex = animation.startingFrame;
	m_state.loop = loop;

	if (m_state.frameIndex < animation.frames.size())
	{
		const SpriteAnimation::Frame& frame = animation.frames[m_state.frameIndex];
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

std::string SpriteAnimatorComponent::getPlayingAnimation() const
{
	if (m_isPlaying)
	{
		return m_state.name;
	}
	return "";
}

json::value SpriteAnimatorComponent::serialize() const
{
	json::value data = Component::serialize();

	json::value anims = json::object();
	for (const auto& pair : animations)
	{
		anims[pair.first] = ::serialize(pair.second->descriptor.id);
	}

	data["autoplay"] = autoplay;
	data["animations"] = anims;
	return data;
}

void SpriteAnimatorComponent::deserialize(const json::value& value)
{
	Component::deserialize(value);
	autoplay = value["autoplay"].as_bool(false);
	const auto& anims = value["animations"].as_object({});
	for (const auto& pair : anims)
	{
		uuid animationId = uuid::Invalid;
		::deserialize(pair.second, animationId);
		animations.insert(std::make_pair(pair.first, AssetLibrary::instance().find<SpriteAnimationAsset>(animationId)));
	}
}

void SpriteAnimatorComponent::updateFrame(const SpriteAnimation::Frame& frame)
{
	if (m_spriteRenderer == nullptr)
	{
		m_spriteRenderer = getOwner()->findComponent<SpriteRendererComponent>();
	}

	if (m_spriteRenderer)
	{
		m_spriteRenderer->sprite = frame.sprite;
	}
}