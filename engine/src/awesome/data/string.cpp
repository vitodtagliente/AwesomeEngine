#include "string.h"

#include <algorithm>
#include <sstream>

namespace awesome
{
	std::vector<std::string> String::split(const std::string& t_str, const char t_delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(t_str);
		while (std::getline(tokenStream, token, t_delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}
	
	bool String::contains(const std::string& t_str, const char t_match)
	{
		return t_str.find(t_match) != std::string::npos;
	}
	
	bool String::contains(const std::string& t_str, const std::string& t_match)
	{
		return t_str.find(t_match) != std::string::npos;
	}
	
	bool String::startsWith(const std::string& t_str, const std::string& t_match, const CompareMode t_mode)
	{
		if (t_mode == CompareMode::CaseSensitive)
		{
			return t_str.find(t_match) == 0;
		}
		else
		{		
			return toLower(t_str).find(toLower(t_match)) == 0;
		}
	}
	
	bool String::endsWith(const std::string& t_str, const std::string& t_match, const CompareMode t_mode)
	{
		return false;
	}
	
	std::string String::toLower(const std::string& t_str)
	{
		std::string result(t_str);
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}
	
	std::string String::toUpper(const std::string& t_str)
	{
		std::string result(t_str);
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		return result;
	}
	
	std::string String::trim(const std::string& t_str)
	{
		return ltrim(rtrim(t_str));
	}

	std::string String::trim(const std::string& t_str, const char t_char)
	{
		return ltrim(rtrim(t_str, t_char), t_char);
	}
	
	std::string String::ltrim(const std::string& t_str)
	{
		std::string result(t_str);
		auto it2 = std::find_if(
			result.begin(), 
			result.end(), 
			[](char ch) 
			{ return !std::isspace(ch); }
		);
		result.erase(result.begin(), it2);
		return result;
	}

	std::string String::ltrim(const std::string& t_str, const char t_char)
	{
		std::string result(t_str);
		auto it2 = std::find_if(
			result.begin(),
			result.end(),
			[t_char](char ch)
			{ return ch != t_char; }
		);
		result.erase(result.begin(), it2);
		return result;
	}
	
	std::string String::rtrim(const std::string& t_str)
	{
		std::string result(t_str);
		auto it1 = std::find_if(
			result.rbegin(), 
			result.rend(), 
			[](char ch) 
			{ return !std::isspace(ch); }
		);
		result.erase(it1.base(), result.end());
		return result;
	}
	
	std::string String::rtrim(const std::string& t_str, const char t_char)
	{
		std::string result(t_str);
		auto it1 = std::find_if(
			result.rbegin(),
			result.rend(),
			[t_char](char ch)
			{ return ch != t_char; }
		);
		result.erase(it1.base(), result.end());
		return result;
	}
	
	std::vector<std::string> String::getLines(const std::string& t_str)
	{
		std::vector<std::string> lines;
		std::istringstream stream(t_str);
		std::string line;
		while (std::getline(stream, line))
		{
			lines.push_back(line);
		}
		return lines;
	}
}