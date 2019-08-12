#include "filesystem.h"

#include <filesystem>
#include <fstream>

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

	std::string File::readAll(const std::string& t_path)
	{
		std::string content;
		std::ifstream file;
		file.open(t_path.c_str(), std::ifstream::in);
		if (file.is_open())
		{
			std::getline(file, content, '\0');
			file.close();
		}
		return content;
	}

	std::vector<std::string> File::readLines(const std::string& t_path)
	{
		std::vector<std::string> lines;

		std::string line{};
		std::ifstream file;
		file.open(t_path.c_str(), std::ifstream::in);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				lines.push_back(line);
			}
			file.close();
		}

		return lines;
	}

}