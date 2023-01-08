#include "sprite_animation_asset_inspector.h"

#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/data/json_file.h>

bool SpriteAnimationAssetInspector::canInspect(const AssetPtr& asset)
{
	return asset->descriptor.type == Asset::Type::SpriteAnimation;
}

void SpriteAnimationAssetInspector::inspect(const AssetPtr& asset)
{
	SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(asset);
	if (animation == nullptr || animation->state != Asset::State::Ready)
	{
		Layout::text("Loading...");
		return;
	}

	SpriteAnimationData& data = animation->data;
	Layout::input(data);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		JsonFile::save(animation->data, animation->descriptor.getDataPath());
	}

	if (Layout::collapsingHeader("Tool"))
	{
		Layout::input("Rect", m_frameRect);
		Layout::input("Duration", m_frameDuration);
		if (Layout::collapsingHeader("Frame Helper Tool"))
		{
			Layout::input("Columns", m_cols);
			Layout::input("Rows", m_rows);
			Layout::input("Column Index", m_columnIndex);
			Layout::input("Row Index", m_rowIndex);
			if (Layout::button(TextIcon::search(" Preview size")))
			{
				m_frameRect.width = static_cast<float>(1.0 / m_cols);
				m_frameRect.height = static_cast<float>(1.0 / m_rows);
			}
			Layout::sameLine();
			if (Layout::button(TextIcon::search(" Preview index")))
			{
				m_frameRect.x = static_cast<float>(m_columnIndex) * static_cast<float>(1.0 / m_cols);
				m_frameRect.y = static_cast<float>(m_rowIndex) * static_cast<float>(1.0 / m_rows);
			}
			Layout::sameLine();
			if (Layout::button(TextIcon::eraser(" Reset")))
			{
				m_frameRect.width = m_frameRect.height = 1.f;
				m_cols = m_rows = 1;
				m_frameRect.x = m_frameRect.y = 0.f;
				m_columnIndex = m_rowIndex = 0;
			}
		}
		Layout::image(data.image, m_frameRect);
		if (Layout::button(TextIcon::plus(" Add")))
		{
			std::unique_ptr<SpriteAnimationFrame> frame = std::make_unique<SpriteAnimationFrame>();
			frame->duration = m_frameDuration;
			frame->rect = m_frameRect;
			data.frames.push_back(std::move(frame));
		}
	}

	Layout::separator();

	// Preview
	const auto& frames = data.frames;
	if (!frames.empty() && m_frameIndex < frames.size())
	{
		Layout::image(data.image, frames[m_frameIndex]->rect);
		Layout::slider("Playing Frame", 0, static_cast<int>(frames.size()) - 1, m_frameIndex);
	}
}

void SpriteAnimationAssetInspector::update(const AssetPtr& asset, const double deltaTime)
{
	SpriteAnimationAssetPtr animation = std::static_pointer_cast<SpriteAnimationAsset>(asset);
	if (animation == nullptr || animation->state != Asset::State::Ready)
	{
		return;
	}

	const bool hasChanged = m_previousSelectedAsset != animation.get();
	m_previousSelectedAsset = animation.get();

	auto& frames = animation->data.frames;

	if (hasChanged)
	{
		m_frameIndex = 0;
		if (!frames.empty())
		{
			m_timeLeft = frames.at(m_frameIndex)->duration;
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
			const auto& frame = frames[m_frameIndex];
			m_timeLeft = frame->duration;
		}
	}
}