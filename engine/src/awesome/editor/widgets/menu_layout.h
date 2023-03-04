/// Copyright (c) Vito Domenico Tagliente
#pragma once

class MenuLayout
{
public:

	static bool beginMainMenu();
	static bool beginMenu(const char* const name);
	static void endMainMenu();
	static void endMenu();
	static bool item(const char* const name);
	static bool item(const char* const name, bool& checked);
	static void separator();
};