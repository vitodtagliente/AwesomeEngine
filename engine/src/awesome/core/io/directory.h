#pragma once

#include <string>
#include <vector>

namespace awesome
{
	struct Directory
	{
		Directory() = delete;
		~Directory() = delete;

		// create a directory 
		static bool create(const std::string& t_path);
		static std::vector<std::string> getDirectories(const std::string& t_path);
		static std::vector<std::string> getFiles(const std::string& t_path);
		// return true if the directory exists
		static bool exists(const std::string& t_path);
		// retrieve the current working directory
		static std::string getCurrentDirectory();

	};
}