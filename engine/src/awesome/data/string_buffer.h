#pragma once

#include <string>
#include <vector>

namespace awesome
{
	namespace data
	{
		class StringBuffer : public std::vector<std::string>
		{
		public:
			inline std::string toString(const bool append_end_lines = true) {
				std::string temp{};
				for (auto& str : *this) {
					temp.append(str);
					if (append_end_lines)
						temp.append("\n");
				}
				return temp;
			}
		};
	}
}