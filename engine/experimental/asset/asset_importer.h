/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

class AssetImporter
{
public:
	AssetImporter() = delete;

	static bool import(const std::filesystem::path& path, bool recursive, bool& newFilesFound);
	static bool import(const std::filesystem::path& path, bool& newFilesFound);

private:
	static bool importDirectory(const std::filesystem::path& path, bool recursive, bool& newFilesFound);
	static bool importFile(const std::filesystem::path& path, bool& newFilesFound);
};