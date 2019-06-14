#pragma once 

#include <map>
#include <string>
#include <awesome/core/singleton.h>

namespace awesome
{
	class Config : public Singleton<Config>
	{
	public:

		Config();
		~Config();

	private:
		
		std::string get_config(const std::string& t_name) const;

		// cached configs
		std::map<std::string, std::string> m_configs;
	};
}