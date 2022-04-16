#include "sprite_animation_inspector.h"

#include <awesome/data/sprite_animation_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	SpriteAnimationInspector::SpriteAnimationInspector()
		: m_previousSelectedAsset()
		, m_timeLeft()
		, m_frameIndex()
	{
	}

	bool SpriteAnimationInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::SpriteAnimation;
	}

	void SpriteAnimationInspector::inspect(const State::Selection& selection)
	{
		SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(selection.asAsset());
		if (animation == nullptr)
		{
			return;
		}

		Layout::input("Frames", animation->data.frames);

		Layout::separator();
		if (Layout::button("Save"))
		{
			animation->data.save(animation->filename.parent_path() / animation->filename.stem());
		}

		const auto& frames = animation->data.frames;
		if (!frames.empty() && m_frameIndex < frames.size())
		{
			const auto& sprite = frames.at(m_frameIndex).sprite;
			if (sprite)
			{
				Layout::image(sprite->data.image, sprite->data.rect);
				Layout::slider("Playing", 0, static_cast<int>(frames.size()) - 1, m_frameIndex);
			}
		}
	}

	void SpriteAnimationInspector::update(const State::Selection& selection, double deltaTime)
	{
		SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(selection.asAsset());
		if (animation == nullptr)
		{
			return;
		}

		const bool hasChanged = m_previousSelectedAsset != animation.get();
		m_previousSelectedAsset = animation.get();

		const auto& frames = animation->data.frames;


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