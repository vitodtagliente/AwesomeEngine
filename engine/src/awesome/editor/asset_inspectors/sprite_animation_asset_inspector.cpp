#include "sprite_animation_asset_inspector.h"

#include <awesome/editor/text_icon.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/editor/widgets/type_layout.h>

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

	FormLayout::asset("Image", spriteAnimation.image);
	FormLayout::input("Starting Frame", spriteAnimation.startingFrame);
	FormLayout::input<SpriteAnimationFrame>(
		"Frames",
		spriteAnimation.frames,
		[](SpriteAnimationFrame& frame) -> void
		{
			FormLayout::input("Rect", frame.rect);
			FormLayout::input("Duration", frame.duration);
		},
		[]() -> SpriteAnimationFrame
		{
			return SpriteAnimationFrame();
		}
	);

	FormLayout::separator();

	if (FormLayout::button(TextIcon::save(" Save").c_str()))
	{
		m_asset.save();
	}

	if (FormLayout::collapsingHeader("Tool"))
	{
		FormLayout::input("Rect", m_frameRect);
		FormLayout::input("Duration", m_frameDuration);
		if (FormLayout::collapsingHeader("Frame Helper Tool"))
		{
			FormLayout::input("Columns", m_cols);
			FormLayout::input("Rows", m_rows);
			FormLayout::input("Column Index", m_columnIndex);
			FormLayout::input("Row Index", m_rowIndex);
			if (FormLayout::button(TextIcon::search(" Preview size").c_str()))
			{
				m_frameRect.width = static_cast<float>(1.0 / m_cols);
				m_frameRect.height = static_cast<float>(1.0 / m_rows);
			}
			FormLayout::sameLine();
			if (FormLayout::button(TextIcon::search(" Preview index").c_str()))
			{
				m_frameRect.x = static_cast<float>(m_columnIndex) * static_cast<float>(1.0 / m_cols);
				m_frameRect.y = static_cast<float>(m_rowIndex) * static_cast<float>(1.0 / m_rows);
			}
			FormLayout::sameLine();
			if (FormLayout::button(TextIcon::eraser(" Reset").c_str()))
			{
				m_frameRect.width = m_frameRect.height = 1.f;
				m_cols = m_rows = 1;
				m_frameRect.x = m_frameRect.y = 0.f;
				m_columnIndex = m_rowIndex = 0;
			}
		}
		FormLayout::image(spriteAnimation.image, m_frameRect);
		if (FormLayout::button(TextIcon::plus(" Add").c_str()))
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
		FormLayout::separator();
		FormLayout::image(spriteAnimation.image, frames[m_frameIndex].rect);
		FormLayout::slider("Playing Frame", 0, static_cast<int>(frames.size()) - 1, m_frameIndex);
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