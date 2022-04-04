/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/data/image_asset.h>
#include <awesome/editor/windows/inspector_window.h>
#include <awesome/graphics/texture_rect.h>

namespace editor
{
	class ImageInspector : public InspectorWindow::Inspector
	{
	public:
		ImageInspector();

		virtual bool canInspect(const State::Selection& selection) override;
		virtual void inspect(const State::Selection& selection, const std::filesystem::path& path) override;

	private:
		ImageAsset* m_previousSelectedAsset;
		std::string m_filename;
	};
}