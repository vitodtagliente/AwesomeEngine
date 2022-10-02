/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <optional>
#include <string>

#include <awesome/editor/utils/dir.h>

class OpenFileDialog
{
public:
	OpenFileDialog();

	inline bool isOpen() const { return m_open; }

	void close();
	void open(const std::string& title, const std::vector<std::string>& extensions, const std::function<void(const std::filesystem::path&)>& handler);
	void render();

private:
	Dir m_dir;
	std::vector<std::string> m_extensions;
	std::function<void(const std::filesystem::path&)> m_handler;
	bool m_open;
	std::filesystem::path m_root;
	std::optional<std::filesystem::path> m_selectedFile;
	std::string m_title;
};