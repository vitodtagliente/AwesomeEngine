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
		return std::string();
	}
	
	std::string String::ltrim(const std::string& t_str)
	{
		return std::string();
	}
	
	std::string String::rtrim(const std::string& t_str)
	{
		return std::string();
	}
}