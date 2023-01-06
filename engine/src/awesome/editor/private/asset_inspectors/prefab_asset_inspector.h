/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>

class Entity;

class PrefabAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	PrefabAssetInspector() = default;
	virtual ~PrefabAssetInspector();

	virtual bool canInspect(const AssetPtr& asset) override;
	virtual void inspect(const AssetPtr& asset) override;

private:
	Entity* m_entity;
	PrefabAssetPtr m_previouslySelectedPrefab;
};