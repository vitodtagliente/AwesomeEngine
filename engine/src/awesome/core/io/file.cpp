#include "file.h"

#include <fstream>

namespace awesome
{
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