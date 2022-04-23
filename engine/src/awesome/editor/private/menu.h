/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/editor/menu_item.h>
#include <awesome/editor/widgets/save_file_dialog.h>

namespace editor
{
	class Menu
	{
	public:
		Menu() = default;

		void init();
		void render();

	private:

		void menuFile();
		void menuAssets();

		std::vector<std::unique_ptr<MenuItem>> m_menuItems;
		SaveFileDialog m_saveFileDialog;
	};
}