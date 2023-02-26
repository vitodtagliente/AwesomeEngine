/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

class AssetImporter
{
public:
	AssetImporter() = delete;

	static void import(const std::filesystem::path& path, bool recursive);
	static bool import(const std::filesystem::path& path);

private:
	static void importDirectory(const std::filesystem::path& path, bool recursive);
	static bool importFile(const std::filesystem::path& path);
};