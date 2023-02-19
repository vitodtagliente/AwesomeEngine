#include "window_layout.h"

#include <imgui.h>

void WindowLayout::begin(const std::string& name)
{
	ImGui::Begin(name.c_str());
}

void WindowLayout::end()
{
	ImGui::End();
}

bool WindowLayout::isFocused()
{
	return ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
}

bool WindowLayout::isHovered()
{
	return ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
}
