#pragma once 

#include <map>
#include <memory>
#include <string>
#include "language.h"

namespace awesome
{
	class Localization
	{
	public:

		Localization();

	private:

		// languages
		std::map<std::string, std::unique_ptr<Language>> m_languages;
		// current language
		Language* m_currentLanguage;
	};
}