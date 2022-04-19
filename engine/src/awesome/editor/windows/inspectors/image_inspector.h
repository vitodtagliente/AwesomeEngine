/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/editor/widgets/save_file_dialog.h>
#include <awesome/editor/windows/inspector_window.h>

namespace editor
{
	class ImageInspector : public InspectorWindow::Inspector
	{
	public:
		ImageInspector() = default;

		virtual bool canInspect(const State::Selection& selection) override;
		virtual void inspect(const State::Selection& selection) override;

	private:
		SaveFileDialog m_saveFileDialog;
	};
}