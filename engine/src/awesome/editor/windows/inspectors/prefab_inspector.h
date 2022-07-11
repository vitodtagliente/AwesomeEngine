/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>
#include <awesome/entity/entity.h>

namespace editor
{
	class PrefabInspector : public AssetInspectorWindow::Inspector
	{
	public:
		PrefabInspector() = default;

		virtual bool canInspect(const AssetPtr& asset) override;
		virtual void inspect(const AssetPtr& asset) override;

	private:
		Entity m_entity;
		PrefabAssetPtr m_previouslySelectedPrefab;
	};
}