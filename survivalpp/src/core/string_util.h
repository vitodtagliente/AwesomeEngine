/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

class StringUtil
{
public:

	StringUtil() = delete;

	enum class CompareMode
	{
		CaseSensitive,
		IgnoreCase
	};

	static std::vector<std::string> split(const std::string& str, char delimiter);

	static bool contains(const std::string& str, const std::string& match, CompareMode mode = CompareMode::CaseSensitive);
	static std::string replace(const std::string& str, const std::string& pattern, const std::string& replacement);

	static bool startsWith(const std::string& str, const std::string& match, CompareMode mode = CompareMode::CaseSensitive);
	static bool endsWith(const std::string& str, const std::string& match, CompareMode mode = CompareMode::CaseSensitive);

	static std::string toLower(const std::string& str);
	static std::string toUpper(const std::string& str);

	static std::string trim(const std::string& str);
	static std::string trim(const std::string& str, char ch);
	static std::string ltrim(const std::string& str);
	static std::string ltrim(const std::string& str, char ch);
	static std::string rtrim(const std::string& str);
	static std::string rtrim(const std::string& str, char ch);

	// retrieve all the string lines
	static std::vector<std::string> getLines(const std::string& str);
};