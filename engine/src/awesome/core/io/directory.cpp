#include "directory.h"

#include <filesystem>

namespace awesome
{
	bool Directory::create(const std::string& t_path)
	{
		return std::filesystem::create_directory(t_path);
	}

	std::vector<std::string> Directory::getDirectories(const std::string& t_path)
	{
		std::vector<std::string> result;
		for (const auto& it : std::filesystem::directory_iterator(std::filesystem::path(t_path)))
		{
			if (it.is_directory())
			{
				result.push_back(it.path().string());
			}
		}
		return result;
	}

	std::vector<std::string> Directory::getFiles(const std::string& t_path)
	{
		std::vector<std::string> result;
		for (const auto& it : std::filesystem::directory_iterator(std::filesystem::path(t_path)))
		{
			if (!it.is_directory())
			{
				result.push_back(it.path().string());
			}
		}
		return result;
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