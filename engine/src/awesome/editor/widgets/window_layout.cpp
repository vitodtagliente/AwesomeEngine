#include "window_layout.h"

#include <imgui.h>

void WindowLayout::begin(char* const name)
{
	ImGui::Begin(name);
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
