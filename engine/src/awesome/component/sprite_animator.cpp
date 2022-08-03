#include "sprite_animator.h"

#include <awesome/asset/asset_library.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

#include "sprite_renderer.h"

namespace component
{
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

	void SpriteAnimator::play(const std::string& name, const bool loop)
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

	std::string SpriteAnimator::getPlayingAnimation() const
	{
		if (m_isPlaying)
		{
			return m_state.name;
		}
		return "";
	}

	json::value SpriteAnimator::serialize() const
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

	void SpriteAnimator::deserialize(const json::value& value)
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

	void SpriteAnimator::inspect()
	{
		Component::inspect();
		editor::Layout::input("Animations", animations);
		editor::Layout::input("Autoplay", autoplay);
	}

	void SpriteAnimator::updateFrame(const SpriteAnimation::Frame& frame)
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
}