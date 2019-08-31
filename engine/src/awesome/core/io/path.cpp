#include "path.h"

#include <filesystem>

namespace awesome
{
	const char Path::directorySeparatorChar = '/';

	std::string Path::combine(const std::string& t_str1, const std::string& t_str2)
	{
		return (std::filesystem::path(t_str1) / std::filesystem::path(t_str2)).string();
	}

	std::string Path::combine(const std::initializer_list<std::string>& t_args)
	{
		std::filesystem::path path;
		for (const std::string& argument : t_args)
		{
			path /= std::filesystem::path(argument);
		}
		return path.string();
	}

	std::string Path::getDirectoryName(const std::string& t_path)
	{
		if (std::filesystem::is_directory(t_path))
		{
			return std::filesystem::path(t_path).filename().string();
		}
		return std::string();
	}

	std::string Path::getExtension(const std::string& t_path)
	{
		return std::filesystem::path(t_path).extension().string();
	}

	std::string Path::getFilename(const std::string& t_path, const bool t_includeExtension)
	{
		std::filesystem::path path(t_path);
		if (t_includeExtension)
		{
			return path.filename().string();
		}
		return path.stem().string();
	}

	bool Path::hasExtension(const std::string& t_path)
	{
		return std::filesystem::path(t_path).has_extension();
	}
}