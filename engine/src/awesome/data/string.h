#pragma once

#include <string>
#include <vector>

namespace awesome
{
	struct String
	{
		enum class CompareMode
		{
			CaseSensitive,
			IgnoreCase
		};

		String() = delete;

		static std::vector<std::string> split(const std::string& t_str, const char t_delimiter);
		static bool contains(const std::string& t_str, const char t_match);
		static bool contains(const std::string& t_str, const std::string& t_match);
		static bool startsWith(const std::string& t_str, const std::string& t_match,
			const CompareMode t_mode = CompareMode::CaseSensitive);
		static bool endsWith(const std::string& t_str, const std::string& t_match,
			const CompareMode t_mode = CompareMode::CaseSensitive);
		static std::string toLower(const std::string& t_str);
		static std::string toUpper(const std::string& t_str);
		static std::string trim(const std::string& t_str);
		static std::string ltrim(const std::string& t_str);
		static std::string rtrim(const std::string& t_str);

	};
}