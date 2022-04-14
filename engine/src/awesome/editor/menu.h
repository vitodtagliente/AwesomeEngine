/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "file_dialog.h"

namespace editor
{
	class Menu
	{
	public:
		Menu() = default;

		void render();

	private:
		FileDialog m_fileDialog;
	};
}