#include "string_util.h"

#include <algorithm>
#include <cctype>
#include <sstream>

std::vector<std::string> StringUtil::split(const std::string& str, const char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

bool StringUtil::contains(const std::string& str, const char match)
{
	return str.find(match) != std::string::npos;
}

bool StringUtil::contains(const std::string& str, const std::string& match)
{
	return str.find(match) != std::string::npos;
}

bool StringUtil::startsWith(const std::string& str, const std::string& match, const CompareMode mode)
{
	if (mode == CompareMode::CaseSensitive)
	{
		return str.find(match) == 0;
	}
	else
	{
		return toLower(str).find(toLower(str)) == 0;
	}
}

bool StringUtil::endsWith(const std::string&, const std::string&, const CompareMode)
{
	return false;
}

std::string StringUtil::toLower(const std::string& str)
{
	std::string result;
	std::transform(str.begin(), str.end(), std::back_inserter(result),
		[](const char c) -> char { return static_cast<char>(std::tolower(c)); }
	);
	return result;
}

std::string StringUtil::toUpper(const std::string& str)
{
	std::string result;
	std::transform(str.begin(), str.end(), std::back_inserter(result),
		[](const char c) -> char { return static_cast<char>(std::toupper(c)); }
	);
	return result;
}

std::string StringUtil::trim(const std::string& str)
{
	return ltrim(rtrim(str));
}

std::string StringUtil::trim(const std::string& str, const char ch)
{
	return ltrim(rtrim(str, ch), ch);
}

std::string StringUtil::ltrim(const std::string& str)
{
	std::string result = str;
	auto it2 = std::find_if(
		result.begin(),
		result.end(),
		[](char ch)
		{ return !std::isspace(ch); }
	);
	result.erase(result.begin(), it2);
	return result;
}

std::string StringUtil::ltrim(const std::string& str, const char ch)
{
	std::string result = str;
	auto it2 = std::find_if(
		result.begin(),
		result.end(),
		[ch](char c)
		{ return ch != c; }
	);
	result.erase(result.begin(), it2);
	return result;
}

std::string StringUtil::rtrim(const std::string& str)
{
	std::string result = str;
	auto it1 = std::find_if(
		result.rbegin(),
		result.rend(),
		[](char ch)
		{ return !std::isspace(ch); }
	);
	result.erase(it1.base(), result.end());
	return result;
}

std::string StringUtil::rtrim(const std::string& str, const char ch)
{
	std::string result = str;
	auto it1 = std::find_if(
		result.rbegin(),
		result.rend(),
		[ch](char c)
		{ return ch != c; }
	);
	result.erase(it1.base(), result.end());
	return result;
}

std::vector<std::string> StringUtil::getLines(const std::string& str)
{
	std::vector<std::string> lines;
	std::istringstream stream(str);
	std::string line;
	while (std::getline(stream, line))
	{
		lines.push_back(line);
	}
	return lines;
}