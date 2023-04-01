#include "search_layout.h"

#include <imgui.h>
#include <imgui_stdlib.h>

#include <awesome/editor/text_icon.h>

#include "form_layout.h"

bool SearchLayout::input(std::string& value)
{
	const std::string previousFilter = value;
	ImGui::PushItemWidth(-1);
	ImGui::InputTextWithHint("filter", TextIcon::search(" Search...").c_str(), &value);
	ImGui::PopItemWidth();
	return previousFilter != value;
}