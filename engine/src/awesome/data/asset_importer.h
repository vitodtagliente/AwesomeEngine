/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <awesome/data/asset.h>

class AssetImporter
{
public:
	AssetImporter() = default;

	void import(const std::filesystem::path& directory, bool recursive);
	bool import(const std::filesystem::path& filename);
};