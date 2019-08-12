#pragma once

#include <map>
#include <string>

namespace awesome
{
	class FileINI
	{
	public:

		class Reader
		{
			Reader() = delete;

			static FileINI parse(const std::string& t_filename);
		};

		FileINI();

	private:

		std::map<std::string, std::map<std::string, std::string>> m_sections;
	};
}