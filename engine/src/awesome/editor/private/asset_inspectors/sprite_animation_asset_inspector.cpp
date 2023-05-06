#include "sprite_animation_asset_inspector.h"

#include <awesome/editor/editor_ui.h>

bool SpriteAnimationAssetInspector::canInspect(int type) const
{
	return type == AssetType_SpriteAnimation;
}

char* const SpriteAnimationAssetInspector::getTitle() const
{
	return "Sprite Animation";
}

void SpriteAnimationAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = SpriteAnimationAsset(record.id);
		m_asset.load();
	}

	if (!m_asset.ready()) return;

	SpriteAnimation& spriteAnimation = *m_asset.resource;
	auto& frames = spriteAnimation.frames;

	if (EditorUI::button((EditorUI::Icon::save + " Save").c_str()))
	{
		m_asset.save();
	}
	EditorUI::separator();

	EditorUI::input("Image", spriteAnimation.image);
	EditorUI::input("Starting Frame", spriteAnimation.startingFrame);
	EditorUI::input<SpriteAnimationFrame>(
		"Frames",
		spriteAnimation.frames,
		[](SpriteAnimationFrame& frame) -> void
		{
			EditorUI::input("Rect", frame.rect);
			EditorUI::input("Duration", frame.duration);
		},
		[]() -> SpriteAnimationFrame
		{
			return SpriteAnimationFrame();
		}
	);

	if (!frames.empty() && m_frameIndex < frames.size())
	{
		EditorUI::separatorText("Preview");
		EditorUI::image(spriteAnimation.image, frames[m_frameIndex].rect);
		EditorUI::slider("Playing Frame", 0, static_cast<int>(frames.size()) - 1, m_frameIndex);
	}
}

void SpriteAnimationAssetInspector::update(const double deltaTime)
{
	if (!m_asset.ready()) return;

	SpriteAnimation& spriteAnimation = *m_asset.resource;
	const auto& frames = spriteAnimation.frames;
	
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
			const auto& frame = frames[m_frameIndex];
			m_timeLeft = frame.duration;
		}
	}
}