#include "string.h"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace awesome
{
	String::String()
		: std::string()
	{

	}

	String::String(const std::string& t_str)
		: std::string(t_str)
	{

	}

	std::vector<String> String::split(const char t_delimiter) const
	{
		std::vector<String> tokens;
		String token;
		std::istringstream tokenStream(*this);
		while (std::getline(tokenStream, token, t_delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	bool String::contains(const char t_match) const
	{
		return find(t_match) != std::string::npos;
	}

	bool String::contains(const std::string& t_match) const
	{
		return find(t_match) != std::string::npos;
	}

	bool String::startsWith(const std::string& t_match,	const CompareMode t_mode) const
	{
		if (t_mode == CompareMode::CaseSensitive)
		{
			return find(t_match) == 0;
		}
		else
		{
			return toLower().find(String(t_match).toLower()) == 0;
		}
	}

	bool String::endsWith(const std::string& t_match, const CompareMode t_mode) const
	{
		return false;
	}

	String String::toLower() const
	{
		String result(*this);
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}

	String String::toUpper() const
	{
		String result(*this);
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		return result;
	}

	String String::trim() const
	{
		return rtrim().ltrim();
	}

	String String::trim(const char t_char) const
	{
		return rtrim(t_char).ltrim(t_char); 
	}

	String String::ltrim() const
	{
		String result(*this);
		auto it2 = std::find_if(
			result.begin(),
			result.end(),
			[](char ch)
			{ return !std::isspace(ch); }
		);
		result.erase(result.begin(), it2);
		return result;
	}

	String String::ltrim(const char t_char) const
	{
		String result(*this);
		auto it2 = std::find_if(
			result.begin(),
			result.end(),
			[t_char](char ch)
			{ return ch != t_char; }
		);
		result.erase(result.begin(), it2);
		return result;
	}

	String String::rtrim() const
	{
		String result(*this);
		auto it1 = std::find_if(
			result.rbegin(),
			result.rend(),
			[](char ch)
			{ return !std::isspace(ch); }
		);
		result.erase(it1.base(), result.end());
		return result;
	}

	String String::rtrim(const char t_char) const
	{
		String result(*this);
		auto it1 = std::find_if(
			result.rbegin(),
			result.rend(),
			[t_char](char ch)
			{ return ch != t_char; }
		);
		result.erase(it1.base(), result.end());
		return result;
	}

	std::vector<String> String::getLines() const
	{
		std::vector<String> lines;
		std::istringstream stream(*this);
		std::string line;
		while (std::getline(stream, line))
		{
			lines.push_back(line);
		}
		return lines;
	}
}