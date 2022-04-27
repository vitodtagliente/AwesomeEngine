/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include "asset.h"

struct AssetFilesystem final
{
	AssetFilesystem() = delete;

	static void move(const Asset::Descriptor& descriptor, const std::filesystem::path& path);
	static bool remove(const Asset::Descriptor& descriptor);
	static void rename(const Asset::Descriptor& descriptor, const std::string& name);

};