#include "string_builder.h"

namespace awesome
{
	StringBuilder::StringBuilder()
		: m_data()
	{
		
	}

	void StringBuilder::append(const std::string& t_str)
	{
		if (m_data.size() > 0)
		{
			m_data.back().append(t_str);
		}
		else
		{
			m_data.push_back(t_str);
		}
	}

	void StringBuilder::appendLine(const std::string& t_str)
	{
		m_data.push_back(t_str);
	}
	
	std::string StringBuilder::toString() const
	{
		std::string result;
		for (const std::string& str : m_data)
		{
			result.append(str);
			result.append("\n");
		}
		return result;
	}
}