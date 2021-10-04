/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <string>
#include <vector>

class StringBuilder
{
public:

	StringBuilder();

	void append(const std::string& text);
	void appendLine(const std::string& line);

	std::string toString() const;

private:

	std::vector<std::string> m_lines;
};