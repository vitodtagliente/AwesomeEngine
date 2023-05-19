/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/asset/data/audio.h>

struct AudioLoader
{
	AudioLoader() = delete;

	static bool load(const std::filesystem::path& path, Audio& audio);
};