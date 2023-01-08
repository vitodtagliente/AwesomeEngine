/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

class JsonFile
{
public:
	JsonFile() = delete;

	static void save(const json::value& data, const std::filesystem::path& path);
	static void save(const Type& type, const std::filesystem::path& path);
	static void save(std::shared_ptr<Type>& type, const std::filesystem::path& path);
	static void save(std::unique_ptr<Type>& type, const std::filesystem::path& path);
	static bool load(const std::filesystem::path& path, json::value& data);
	static bool load(const std::filesystem::path& path, Type& type);
	static bool load(const std::filesystem::path& path, std::shared_ptr<Type>& type);
	static bool load(const std::filesystem::path& path, std::unique_ptr<Type>& type);
};