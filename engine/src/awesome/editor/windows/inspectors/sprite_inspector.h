/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/data/sprite_asset.h>
#include <awesome/editor/windows/inspector_window.h>

namespace editor
{
	class SpriteInspector : public InspectorWindow::Inspector
	{
	public:
		SpriteInspector();

		virtual bool canInspect(const State::Selection& selection) override;
		virtual void inspect(const State::Selection& selection, const std::filesystem::path&) override;

	private:
		SpriteAsset* m_previousSelectedAsset;
		std::string m_filename;
	};
}