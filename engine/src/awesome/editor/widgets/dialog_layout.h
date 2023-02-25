/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "save_file_dialog.h"

struct DialogLayout final
{
	friend class Editor;

	DialogLayout() = delete;

	static void save(const std::string& title, const std::string& extension, const std::function<void(const std::filesystem::path&)>& handler);

private:
	static void render();
	static SaveFileDialog s_saveFileDialog;
};