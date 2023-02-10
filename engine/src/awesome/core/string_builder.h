/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <sstream>
#include <string>
#include <vector>

class StringBuilder
{
public:
	StringBuilder() = default;

	void push(const std::string& token);
	template<typename... Ts>
	void push(Ts const&... ts)
	{
		const std::string str = string_format(ts...);
		push(str);
	}

	void push_line(const std::string& line);
	template<typename... Ts>
	void push_line(Ts const&... ts)
	{
		const std::string str = string_format(ts...);
		push_line(str);
	}

	std::string string() const;

private:

	template<typename... Ts>
	std::string string_format(Ts const&... ts) {
		std::stringstream s;
		int dummy[] = { 0, ((s << ts), 0)... };
		static_cast<void>(dummy); // Avoid warning for unused variable
		return s.str();
	}

	std::vector<std::string> m_lines;
};