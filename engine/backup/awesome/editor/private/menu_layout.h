/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

class MenuLayout
{
public:

	static bool beginMainMenu();
	static bool beginMenu(const std::string& name);
	static void endMainMenu();
	static void endMenu();
	static bool item(const std::string& name);
	static bool item(const std::string& name, bool& checked);
	static void separator();
};