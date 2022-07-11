/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/windows/asset_inspector_window.h>

namespace editor
{
	class TextInspector : public AssetInspectorWindow::Inspector
	{
	public:
		TextInspector() = default;

		virtual bool canInspect(const AssetPtr& asset) override;
		virtual void inspect(const AssetPtr& asset) override;
	};
}