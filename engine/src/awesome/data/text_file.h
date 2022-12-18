/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

class TextFile
{
public:
	TextFile() = delete;

	static void save(const std::string& data, const std::filesystem::path& path);
	static bool load(const std::filesystem::path& path, std::string& data);
};