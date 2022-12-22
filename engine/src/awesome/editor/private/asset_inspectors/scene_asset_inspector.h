/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/windows/asset_inspector_window.h>

class SceneAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	SceneAssetInspector() = default;

	virtual bool canInspect(const AssetPtr& asset) override;
	virtual void inspect(const AssetPtr& asset) override;
};