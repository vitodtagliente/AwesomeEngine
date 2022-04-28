/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/core/uuid.h>

class AssetImporter
{
public:
	AssetImporter() = default;

	void import(const std::filesystem::path& path, bool recursive);
	bool import(const std::filesystem::path& path, uuid& id);
	bool import(const std::filesystem::path& path);

private:
	void importDirectory(const std::filesystem::path& path, bool recursive);
	bool importFile(const std::filesystem::path& path, uuid& id);
};