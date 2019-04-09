#include <awesome/data/string.h>

#include <algorithm> 
#include <cctype>
#include <locale>
#include <sstream>

namespace awesome
{
	namespace data
	{
		std::string String::ltrim(const std::string& str)
		{
			auto s = str;
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
				return !std::isspace(ch);
			}));
			return s;
		}

		std::string String::rtrim(const std::string& str)
		{
			auto s = str;
			s.erase(std::find_if(s.rbegin(), s.rend(), [](const int ch) {
				return !std::isspace(ch);
			}).base(), s.end());
			return s;
		}

		std::string String::trim(const std::string& str)
		{
			return ltrim(rtrim(str));
		}

		std::string String::lower(const std::string& str)
		{
			std::string temp = str;
			std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			return temp;
		}

		std::string String::upper(const std::string& str)
		{
			std::string temp = str;
			std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
			return temp;
		}

		bool String::contains(const std::string& str, const std::string& substr)
		{
			return (str.find(substr) != std::string::npos);
		}

		std::vector<std::string> String::split(const std::string& str, const std::string& delimiter)
		{
			std::vector<std::string> elems;
			std::size_t previous = 0;
			std::size_t current = str.find_first_of(delimiter);
			while (current != std::string::npos) {
				elems.push_back(str.substr(previous, current - previous));
				previous = current + 1;
				current = str.find_first_of(delimiter, previous);
			}
			elems.push_back(str.substr(previous, current - previous));
			return elems;
		}

		bool String::isEqual(const std::string& str1, const std::string& str2, const bool ignore_case)
		{
			if(ignore_case)
			{
				return lower(str1) == lower(str2);
			}
			else return str1 == str2;
		}

	}
}