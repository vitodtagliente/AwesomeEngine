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

	EditorUI::separator();

	if (EditorUI::button((EditorUI::Icon::save + " Save").c_str()))
	{
		m_asset.save();
	}

	if (EditorUI::collapsingHeader("Tool"))
	{
		EditorUI::input("Rect", m_frameRect);
		EditorUI::input("Duration", m_frameDuration);
		if (EditorUI::collapsingHeader("Frame Helper Tool"))
		{
			EditorUI::input("Columns", m_cols);
			EditorUI::input("Rows", m_rows);
			EditorUI::input("Column Index", m_columnIndex);
			EditorUI::input("Row Index", m_rowIndex);
			if (EditorUI::button((EditorUI::Icon::search + " Preview size").c_str()))
			{
				m_frameRect.width = static_cast<float>(1.0 / m_cols);
				m_frameRect.height = static_cast<float>(1.0 / m_rows);
			}
			EditorUI::sameLine();
			if (EditorUI::button((EditorUI::Icon::search + " Preview index").c_str()))
			{
				m_frameRect.x = static_cast<float>(m_columnIndex) * static_cast<float>(1.0 / m_cols);
				m_frameRect.y = static_cast<float>(m_rowIndex) * static_cast<float>(1.0 / m_rows);
			}
			EditorUI::sameLine();
			if (EditorUI::button((EditorUI::Icon::eraser + " Reset").c_str()))
			{
				m_frameRect.width = m_frameRect.height = 1.f;
				m_cols = m_rows = 1;
				m_frameRect.x = m_frameRect.y = 0.f;
				m_columnIndex = m_rowIndex = 0;
			}
		}
		EditorUI::image(spriteAnimation.image, m_frameRect);
		if (EditorUI::button((EditorUI::Icon::plus + " Add").c_str()))
		{
			SpriteAnimationFrame frame;
			frame.duration = m_frameDuration;
			frame.rect = m_frameRect;
			frames.push_back(frame);
		}
	}

	// Live preview
	if (!frames.empty() && m_frameIndex < frames.size())
	{
		EditorUI::separator();
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