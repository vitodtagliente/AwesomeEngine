#include "ini.h"

#include <awesome/core/filesystem.h>
#include "string.h"

namespace awesome
{
	FileINI FileINI::Reader::parse(const std::string& t_filename)
	{
		/*
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
		*/
		return {};
	}

	FileINI::FileINI()
		: m_sections()
	{

	}
	
	bool FileINI::hasSection(const std::string& t_name) const
	{
		return m_sections.find(t_name) != m_sections.end();
	}

	FileINI::Section& FileINI::getSection(const std::string& t_name)
	{
		return m_sections[t_name];
	}
	
	bool FileINI::Section::contains(const std::string& t_key) const
	{
		return m_data.find(t_key) != m_data.end();
	}
	
	std::string FileINI::Section::get(const std::string& t_key) const
	{
		auto it = m_data.find(t_key);
		if (it != m_data.end())
		{
			return it->second;
		}
		return std::string();
	}
	
	void FileINI::Section::set(const std::string& t_key, const std::string& t_value)
	{
		auto it = m_data.find(t_key);
		if (it != m_data.end())
		{
			it->second = t_value;
		}
	}
	
	void FileINI::Section::remove(const std::string& t_key)
	{
		m_data.erase(t_key);
	}
	
	std::string FileINI::Section::to_string() const
	{
		std::string result;

		result.append("[").append(m_name).append("]\n");
		for (const auto& pair : m_data)
		{
			result.append(pair.first).append("=").append(pair.second).append("\n");
		}

		return result;
	}
}