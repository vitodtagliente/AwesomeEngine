#pragma once

#include <string>
#include <vector>

namespace awesome
{
	class StringBuilder
	{
	public:

		StringBuilder();

		void append(const std::string& t_str);
		void appendLine(const std::string& t_str);

		std::string toString() const;

	private:

		std::vector<std::string> m_data;
	};
}