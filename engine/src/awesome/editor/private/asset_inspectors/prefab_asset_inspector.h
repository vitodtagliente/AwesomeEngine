/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>
#include <awesome/entity/entity.h>

class PrefabAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	PrefabAssetInspector() = default;

	virtual bool canInspect(const AssetPtr& asset) override;
	virtual void inspect(const AssetPtr& asset) override;

private:
	Entity m_entity;
	PrefabAssetPtr m_previouslySelectedPrefab;
};