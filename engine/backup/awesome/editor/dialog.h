/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/singleton.h>

#include "widgets/open_file_dialog.h"
#include "widgets/save_file_dialog.h"

class Dialog : public Singleton<Dialog>
{
public:
	void open(const std::string& title, const std::vector<std::string>& extensions, const std::function<void(const std::filesystem::path&)>& handler);
	void save(const std::string& title, const std::string& extension, const std::function<void(const std::filesystem::path&)>& handler);

	void render();

private:
	OpenFileDialog m_openFileDialog;
	SaveFileDialog m_saveFileDialog;
};