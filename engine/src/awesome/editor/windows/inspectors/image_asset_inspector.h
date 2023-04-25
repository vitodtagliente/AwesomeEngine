/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/asset/image_asset.h>

class ImageAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	virtual bool canInspect(const AssetRecord* const record) override;
	virtual void inspect(const AssetRecord* const record) override;

protected:
	ImageAsset m_imageAsset;
};