/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/windows/asset_inspector_window.h>

class PrefabAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	virtual bool canInspect(const AssetRecord* const record) override;
	virtual void inspect(const AssetRecord* const record) override;
};