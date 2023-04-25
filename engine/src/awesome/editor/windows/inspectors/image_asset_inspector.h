/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>

class ImageAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	virtual bool canInspect(const AssetRecord& record) override;
	virtual void inspect(const AssetRecord& record) override;

protected:
	ImageAsset m_asset;
};