#pragma once

#include <map>
#include <string>

namespace awesome
{
	class Language 
	{
	public:

		std::string get(const std::string& t_name) const;

	private:

		// language texts
		std::map<std::string, std::string> texts;
	};
}