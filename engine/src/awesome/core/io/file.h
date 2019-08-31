#pragma once

#include <string>
#include <vector>

namespace awesome
{
	struct File
	{
		File() = delete;
		~File() = delete;

		// read all text and close the file
		static std::string readAll(const std::string& t_path);
		// read all lines
		static std::vector<std::string> readLines(const std::string& t_path);
	};
}