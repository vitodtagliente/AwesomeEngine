#include "menu_layout.h"

#include <imgui.h>

bool MenuLayout::beginMainMenu()
{
	return ImGui::BeginMainMenuBar();
}

bool MenuLayout::beginMenu(const char* const name)
{
	return ImGui::BeginMenu(name);
}

void MenuLayout::endMainMenu()
{
	ImGui::EndMainMenuBar();
}

void MenuLayout::endMenu()
{
	ImGui::EndMenu();
}

bool MenuLayout::item(const char* const name)
{
	return ImGui::MenuItem(name);
}

bool MenuLayout::item(const char* const name, bool& checked)
{
	return ImGui::MenuItem(name, nullptr, &checked);
}

void MenuLayout::separator()
{
	ImGui::Separator();
}