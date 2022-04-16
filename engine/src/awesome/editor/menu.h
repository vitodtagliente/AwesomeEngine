/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/widgets/save_file_dialog.h>

namespace editor
{
	class Menu
	{
	public:
		Menu();

		void render();

	private:
		SaveFileDialog m_fileDialog;
	};
}