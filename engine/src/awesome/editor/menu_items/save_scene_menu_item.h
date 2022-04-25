/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/editor/menu_item.h>
#include <awesome/editor/widgets/save_file_dialog.h>

namespace editor
{
	class SaveSceneMenuItem : public MenuItem
	{
	public:
		SaveSceneMenuItem() = default;
		virtual ~SaveSceneMenuItem() = default;

		virtual std::string getCategory() const override { return "Scene"; };
		virtual std::string getName() const override { return "Save Scene"; };

		virtual void render() override;
		virtual void execute() override;

		REFLECT()

	private:
		SaveFileDialog m_saveFileDialog;
	};
}