#include "filesystem.h"

#include <filesystem>

namespace awesome
{
	const char Path::directorySeparatorChar = '/';

	std::string Path::combine(const std::string& t_str1, const std::string& t_str2)
	{
		return std::filesystem::path(t_str1).append(t_str2).string();
	}

	std::string Path::combine(const std::initializer_list<std::string>& t_args)
	{
		std::filesystem::path path;
		for (const std::string& argument : t_args)
		{
			path.append(argument);
		}
		return path.string();
	}

	std::string Path::getDirectoryName(const std::string& t_path)
	{
		return std::string();
	}

	std::string Path::getExtension(const std::string& t_path)
	{
		return std::string();
	}

	std::string Path::getFilename(const std::string& t_path, const bool t_includeExtension)
	{
		return std::string();
	}

	bool Path::hasExtension(const std::string& t_path)
	{
		return false;
	}

	bool Directory::create(const std::string& t_name)
	{
		return false;
	}

	std::vector<std::string> Directory::getDirectories(const std::string& t_path)
	{
		return std::vector<std::string>();
	}

	std::vector<std::string> Directory::getFiles(const std::string& t_path)
	{
		return std::vector<std::string>();
	}

	bool Directory::exists(const std::string& t_path)
	{
		return std::filesystem::exists(t_path) && std::filesystem::is_directory(t_path);
	}

	std::string Directory::getCurrentDirectory()
	{
		return std::filesystem::current_path().string();
	}

}