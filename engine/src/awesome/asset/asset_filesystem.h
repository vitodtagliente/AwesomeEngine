/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

struct AssetFilesystem final
{
	AssetFilesystem() = delete;

	static bool erase(const std::filesystem::path& path);
	static bool move(const std::filesystem::path& from, const std::filesystem::path& to);
	static bool rename(const std::filesystem::path& path, const std::string& name);
};