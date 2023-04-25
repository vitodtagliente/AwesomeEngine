/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>

class PrefabAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	virtual bool canInspect(const AssetRecord& record) override;
	virtual void inspect(const AssetRecord& record) override;

protected:
	PrefabAsset m_asset;
};