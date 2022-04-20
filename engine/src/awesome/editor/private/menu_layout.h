/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

namespace editor
{
	class MenuLayout
	{
	public:

		static bool beginMainMenu();
		static bool beginMenu(const std::string& name);
		static void endMainMenu();
		static void endMenu();
		static bool item(const std::string& name);
		static void separator();
	};
}