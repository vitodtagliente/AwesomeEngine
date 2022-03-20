/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

namespace editor
{
	struct File
	{
		File();
		File(const std::filesystem::path& path);
		File(const File& other);

		bool exists() const;

		File& operator= (const File& other);
		bool operator== (const File& other) const;
		bool operator!= (const File& other) const;

		std::string path;
		std::string name;
		std::string extension;
		bool isDirectory;
	};
}