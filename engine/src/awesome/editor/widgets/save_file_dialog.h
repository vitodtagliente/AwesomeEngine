/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <string>

#include <awesome/data/directory.h>

class SaveFileDialog
{
public:
	SaveFileDialog();

	inline bool isOpen() const { return m_open; }

	void close();
	void open(const std::string& title, const std::string& extension, const std::function<void(const std::filesystem::path&)>& handler);
	void render();

private:
	Directory m_directory;
	std::string m_extension;
	std::string m_filename;
	std::function<void(const std::filesystem::path&)> m_handler;
	bool m_open;
	std::filesystem::path m_root;
	std::string m_title;
};