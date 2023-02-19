#include "tree_layout.h"

#include <imgui.h>

bool TreeLayout::begin(const char* const name, const bool selected)
{
	return ImGui::TreeNodeEx(name, ImGuiTreeNodeFlags_OpenOnArrow | (selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None));
}

void TreeLayout::end()
{
	ImGui::TreePop();
}
