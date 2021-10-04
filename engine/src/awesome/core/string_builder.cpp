#include "string_builder.h"

namespace awesome
{

StringBuilder::StringBuilder()
	: m_lines()
{
		
}

void StringBuilder::append(const std::string& text)
{
	if (text.size() > 0)
	{
		m_lines.back().append(text);
	}
	else
	{
		m_lines.push_back(text);
	}
}

void StringBuilder::appendLine(const std::string& t_str)
{
	m_lines.push_back(t_str);
}
	
std::string StringBuilder::toString() const
{
	std::string result;
	for (const std::string& line : m_lines)
	{
		result.append(line);
		result.append("\n");
	}
	return result;
}

} // awesome