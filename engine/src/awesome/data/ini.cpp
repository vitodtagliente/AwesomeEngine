#include "ini.h"

#include <awesome/core/filesystem.h>
#include "string.h"

namespace awesome
{
	FileINI FileINI::Reader::parse(const std::string& t_filename)
	{
		FileINI file;
		std::string currentSection;
		for (const std::string& line : File::readLines(t_filename))
		{
			if (String::contains(line, "[") && String::contains(line, "]"))
			{
				// #todo
				currentSection = String::trim(line);
			}
			else if(String::contains(line, "=") && !currentSection.empty())
			{
				const std::vector<std::string>& tokens = String::split(line, '=');
				file.m_data[currentSection].insert(
					{ String::trim(tokens[0]), String::trim(tokens[1]) }
				);
			}
		}
		return file;
	}

	FileINI::FileINI()
		: m_data()
	{

	}
	
	bool FileINI::hasSection(const std::string& t_name) const
	{
		return m_data.find(t_name) != m_data.end();
	}
}