/// Copyright (c) Vito Domenico Tagliente
#pragma once

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

		void menuAssets();
		void menuFile();
		void menuScene();
		void menuView();

		std::vector<MenuItemPtr> m_menuItems;
		SaveFileDialog m_saveFileDialog;
	};
}