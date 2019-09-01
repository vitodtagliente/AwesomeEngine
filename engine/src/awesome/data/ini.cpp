#include "ini.h"

#include <awesome/core/string.h>

namespace awesome
{	
	bool IniData::hasSection(const std::string& t_name) const
	{
		return m_sections.find(t_name) != m_sections.end();
	}

	IniData::Section& IniData::getSection(const std::string& t_name)
	{
		return m_sections[t_name];
	}

	void IniData::addSection(const Section& t_section)
	{
		m_sections.insert({ t_section.getName(), t_section });
	}

	std::string IniData::toString() const
	{
		std::string result;

		for (const auto& pair : m_sections)
		{
			result.append(pair.second.toString()).append("\n"); 
		}

		return result;
	}

	IniData IniData::parse(const std::string& t_content)
	{
		IniData data;
		 
		std::string currentSection;
		for (const String& line : String(t_content).getLines())
		{
			if (line.contains("[") && line.contains("]"))
			{
				currentSection = line.trim().ltrim('[').rtrim(']').trim();
				data.addSection(Section(currentSection));
			}
			else if (line.contains("=") && !currentSection.empty())
			{
				const std::vector<String>& tokens = line.split('=');

				data.getSection(currentSection)
					.set(tokens[0].trim(), tokens[1].trim());
			}
		}

		return data;
	}
	
	bool IniData::Section::contains(const std::string& t_key) const
	{
		return m_data.find(t_key) != m_data.end();
	}
	
	std::string IniData::Section::get(const std::string& t_key) const
	{
		auto it = m_data.find(t_key);
		if (it != m_data.end())
		{
			return it->second;
		}
		return std::string();
	}

	const std::string& IniData::Section::get(const std::string& t_key, const std::string& t_default) const
	{
		auto it = m_data.find(t_key);
		if (it != m_data.end())
		{
			return it->second;
		}
		return t_default;
	}
	
	void IniData::Section::set(const std::string& t_key, const std::string& t_value)
	{
		auto it = m_data.find(t_key);
		if (it != m_data.end())
		{
			it->second = t_value;
		}
		else
		{
			m_data.insert({ t_key, t_value });
		}
	}
	
	void IniData::Section::remove(const std::string& t_key)
	{
		m_data.erase(t_key);
	}
	
	std::string IniData::Section::toString() const
	{
		std::string result;

		result.append("[").append(m_name).append("]").append("\n");
		for (const auto& pair : m_data)
		{
			result.append(pair.first).append("=").append(pair.second).append("\n");
		}

		return result;
	}
}