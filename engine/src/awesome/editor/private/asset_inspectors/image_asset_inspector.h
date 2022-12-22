/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>
#include <awesome/math/vector2.h>

class ImageAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	ImageAssetInspector() = default;

	virtual bool canInspect(const AssetPtr& asset) override;
	virtual void inspect(const AssetPtr& asset) override;

private:
	int m_columns{ 1 };
	math::vec2 m_padding;
	ImageAssetPtr m_previouslySelectedImage;
	int m_rows{ 1 };
};