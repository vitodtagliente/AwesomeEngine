/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>
#include <awesome/graphics/texture_rect.h>

class SpriteAnimationAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	SpriteAnimationAssetInspector() = default;

	virtual bool canInspect(const AssetPtr& asset) override;
	virtual void inspect(const AssetPtr& asset) override;
	virtual void update(const AssetPtr& asset, double deltaTime) override;

private:
	SpriteAnimationAsset* m_previousSelectedAsset;
	double m_timeLeft;
	int m_frameIndex;
	graphics::TextureRect m_frameRect;
	double m_frameDuration{ 1.0 };
	int m_cols{ 1 };
	int m_rows{ 1 };
	int m_rowIndex{ 0 };
	int m_columnIndex{ 0 };
};