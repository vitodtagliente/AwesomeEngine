/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/editor/windows/asset_inspector_window.h>
#include <awesome/editor/widgets/save_file_dialog.h>
#include <awesome/math/vector2.h>

namespace editor
{
	class ImageInspector : public AssetInspectorWindow::Inspector
	{
	public:
		ImageInspector() = default;

		virtual bool canInspect(const AssetPtr& asset) override;
		virtual void inspect(const AssetPtr& asset) override;

	private:
		int m_columns;
		math::vec2 m_padding;
		ImageAssetPtr m_previouslySelectedImage;
		int m_rows;
		SaveFileDialog m_saveFileDialog;
	};
}