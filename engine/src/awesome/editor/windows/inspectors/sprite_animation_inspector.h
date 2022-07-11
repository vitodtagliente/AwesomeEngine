/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>

namespace editor
{
	class SpriteAnimationInspector : public AssetInspectorWindow::Inspector
	{
	public:
		SpriteAnimationInspector() = default;

		virtual bool canInspect(const AssetPtr& asset) override;
		virtual void inspect(const AssetPtr& asset) override;
		virtual void update(const AssetPtr& asset, double deltaTime) override;

	private:
		SpriteAnimationAsset* m_previousSelectedAsset;
		double m_timeLeft;
		int m_frameIndex;
	};
}