#include "sprite_animation_inspector.h"

#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	bool SpriteAnimationInspector::canInspect(const AssetPtr& asset)
	{
		return asset->descriptor.type == Asset::Type::SpriteAnimation;
	}

	void SpriteAnimationInspector::inspect(const AssetPtr& asset)
	{
		SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(asset);
		if (animation == nullptr)
		{
			return;
		}

		if (!animation->data.has_value())
		{
			Layout::text("Loading...");
			return;
		}

		SpriteAnimation& data = animation->data.value();
		Layout::input("Frames", data.frames);

		const auto& frames = data.frames;
		if (!frames.empty() && m_frameIndex < frames.size())
		{
			const auto& sprite = frames.at(m_frameIndex).sprite;
			if (sprite && sprite->data.has_value())
			{
				Layout::image(sprite->data.value().image, sprite->data.value().rect);
				Layout::slider("Playing", 0, static_cast<int>(frames.size()) - 1, m_frameIndex);
			}
		}

		Layout::separator();

		if (Layout::button(TextIcon::save(" Save")))
		{
			animation->data.value().save(animation->descriptor.path.parent_path() / animation->descriptor.path.stem());
		}
	}

	void SpriteAnimationInspector::update(const AssetPtr& asset, const double deltaTime)
	{
		SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(asset);
		if (animation == nullptr || !animation->data.has_value())
		{
			return;
		}

		const bool hasChanged = m_previousSelectedAsset != animation.get();
		m_previousSelectedAsset = animation.get();

		auto& frames = animation->data.value().frames;
		
		if (hasChanged)
		{
			m_frameIndex = 0;
			if (!frames.empty())
			{
				m_timeLeft = frames.at(m_frameIndex).duration;
			}
		}

		m_timeLeft -= deltaTime;
		if (m_timeLeft <= 0)
		{
			++m_frameIndex;
			if (m_frameIndex >= frames.size())
			{
				m_frameIndex = 0;
			}

			if (m_frameIndex < frames.size())
			{
				const SpriteAnimation::Frame& frame = frames[m_frameIndex];
				m_timeLeft = frame.duration;
			}
		}
	}
}