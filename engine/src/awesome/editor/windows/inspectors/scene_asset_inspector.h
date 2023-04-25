/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/scene_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>

class SceneAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	virtual bool canInspect(const AssetRecord& record) override;
	virtual void inspect(const AssetRecord& record) override;

protected:
	SceneAsset m_asset;
};