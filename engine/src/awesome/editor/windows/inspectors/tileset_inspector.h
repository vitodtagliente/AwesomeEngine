/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/windows/asset_inspector_window.h>

namespace editor
{
	class TilesetInspector : public AssetInspectorWindow::Inspector
	{
	public:
		TilesetInspector() = default;

		virtual bool canInspect(const AssetPtr& asset) override;
		virtual void inspect(const AssetPtr& asset) override;
	};
}