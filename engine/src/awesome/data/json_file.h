/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/encoding/json.h>

class JsonFile
{
public:
	JsonFile() = delete;

	static void save(const json::value& data, const std::filesystem::path& path);
	static bool load(const std::filesystem::path& path, json::value& data);
};