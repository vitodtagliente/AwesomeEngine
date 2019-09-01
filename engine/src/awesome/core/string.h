#pragma once

#include <string>
#include <vector>

namespace awesome
{
	class String : public std::string
	{
	public:

		String();
		String(const std::string& t_str);

		enum class CompareMode
		{
			CaseSensitive,
			IgnoreCase
		};

		std::vector<String> split(const char t_delimiter) const;

		bool contains(const char t_match) const;
		bool contains(const std::string& t_match) const;

		bool startsWith(const std::string& t_match,
			const CompareMode t_mode = CompareMode::CaseSensitive) const;
		bool endsWith(const std::string& t_match,
			const CompareMode t_mode = CompareMode::CaseSensitive) const;

		String toLower() const;
		String toUpper() const;

		String trim() const;
		String trim(const char t_char) const;
		String ltrim() const;
		String ltrim(const char t_char) const;
		String rtrim() const;
		String rtrim(const char t_char) const;

		// retrieve all the string lines
		std::vector<String> getLines() const;
	};
}