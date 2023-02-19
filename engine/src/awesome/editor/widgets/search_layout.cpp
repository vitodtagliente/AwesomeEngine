#include "search_layout.h"

#include <imgui.h>

#include <awesome/editor/text_icon.h>

#include "form_layout.h"

bool SearchLayout::input(std::string& value)
{
	FormLayout::beginChild("Header", 0.f, 26.f);
	const std::string previousFilter = value;
	FormLayout::input(TextIcon::search().c_str(), value);
	FormLayout::endChild();
	return previousFilter != value;
}