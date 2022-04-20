#include "menu_layout.h"

#include <imgui.h>

namespace editor
{
	bool MenuLayout::beginMainMenu()
	{
		return ImGui::BeginMainMenuBar();
	}

	bool MenuLayout::beginMenu(const std::string& name)
	{
		return ImGui::BeginMenu(name.c_str());
	}

	void MenuLayout::endMainMenu()
	{
		ImGui::EndMainMenuBar();
	}

	void MenuLayout::endMenu()
	{
		ImGui::EndMenu();
	}

	bool MenuLayout::item(const std::string& name)
	{
		return ImGui::MenuItem(name.c_str());
	}
	
	void MenuLayout::separator()
	{
		ImGui::Separator();
	}
}