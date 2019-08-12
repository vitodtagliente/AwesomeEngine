#include "ini.h"

#include <awesome/core/filesystem.h>

namespace awesome
{
	FileINI FileINI::Reader::parse(const std::string& t_filename)
	{
		FileINI file;
		std::string currentSection;
		for (const std::string& line : File::readLines(t_filename))
		{

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