/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/core/reflection.h>

class TypeFile
{
public:
	TypeFile() = delete;

	static void save(const IType& data, const std::filesystem::path& path);
	static bool load(const std::filesystem::path& path, IType& data);
};