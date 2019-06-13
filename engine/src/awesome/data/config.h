#pragma once 

#include <map>
#include <awesome/core/singleton.h>
#include <awesome/data/string_id.h>

namespace awesome
{
	class Config : public Singleton<Config>
	{
	public:

		Config();
		~Config();

	};
}