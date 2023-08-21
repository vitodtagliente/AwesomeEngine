#include "string_builder.h"

void StringBuilder::push(const std::string& token)
{
	if (m_lines.empty())
	{
		m_lines.push_back(token);
	}
	else
	{
		m_lines[m_lines.size() - 1] += token;
	}
}

void StringBuilder::push_line(const std::string& line)
{
	m_lines.push_back(line);
}

std::string StringBuilder::string() const
{
	std::string content;
	for (const std::string& line : m_lines)
	{
		content += line + "\n";
	}
	return content;
}