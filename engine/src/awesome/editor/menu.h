/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/widgets/save_file_dialog.h>

namespace editor
{
	class Menu
	{
	public:
		Menu() = default;

		void render();

	private:

		void menuFile();
		void menuAssets();

		SaveFileDialog m_saveFileDialog;
	};
}