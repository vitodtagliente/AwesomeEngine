#include "interaction_layout.h"

#include <imgui.h>

bool InteractionLayout::isKeyDown(const keycode_t keycode)
{
	return ImGui::IsKeyDown(keycode);
}

bool InteractionLayout::isKeyPressed(const keycode_t keycode)
{
	return ImGui::IsKeyPressed(keycode);
}

bool InteractionLayout::isKeyReleased(const keycode_t keycode)
{
	return ImGui::IsKeyReleased(keycode);
}

bool InteractionLayout::isItemHovered()
{
	return ImGui::IsItemHovered();
}

bool InteractionLayout::isMouseClicked()
{
	return ImGui::IsMouseClicked(ImGuiMouseButton_Left);
}

void InteractionLayout::scroll(const float position)
{
	ImGui::SetScrollHereY(position);
}

void InteractionLayout::scrollToBottom()
{
	scroll(1.f);
}
