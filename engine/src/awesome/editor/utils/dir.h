/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

namespace editor
{
	struct Dir
	{
		Dir(const std::filesystem::path& path, bool scanAssetsOnly = true);

		std::vector<std::filesystem::path> files;
		std::filesystem::path parent;
		std::filesystem::path path;
	};
}