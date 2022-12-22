/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/windows/asset_inspector_window.h>

class TextAssetInspector : public AssetInspectorWindow::AssetInspector
{
public:
	TextAssetInspector() = default;

	virtual bool canInspect(const AssetPtr& asset) override;
	virtual void inspect(const AssetPtr& asset) override;
};