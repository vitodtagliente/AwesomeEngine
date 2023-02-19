#include "layout.h"

#include <filesystem>

#include <imgui.h>
#include <imgui_stdlib.h>

#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>

std::vector<std::string> Layout::s_context;
std::map<std::string, void*> Layout::s_keyCache{};

void Layout::begin(const std::string& name)
{
	ImGui::Begin(id(name).c_str());
}

void Layout::beginChild(const std::string& name)
{
	ImGui::BeginChild(name.c_str(), ImVec2(0.f, 0.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
}

void Layout::beginChild(const std::string& name, const float width, const float height)
{
	ImGui::BeginChild(name.c_str(), ImVec2(width, height), false, ImGuiWindowFlags_NoDecoration);
}

void Layout::beginContext(const std::string context)
{
	s_context.push_back(context);
}

bool Layout::beginTreeNode(const std::string& name, const bool selected)
{
	return ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | (selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None));
}

bool Layout::button(const std::string& name)
{
	return ImGui::Button(id(name).c_str());
}

bool Layout::button(const std::string& name, const int width, const int height)
{
	return ImGui::Button(id(name).c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height)));
}

bool Layout::button(const std::string& name, const graphics::Color& color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(id(name).c_str());
	ImGui::PopStyleColor(3);
	return result;
}

bool Layout::button(const std::string& name, const graphics::Color& color, const int width, const int height)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(id(name).c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height)));
	ImGui::PopStyleColor(3);
	return result;
}

bool Layout::collapsingHeader(const std::string& name)
{
	return ImGui::CollapsingHeader(id(name).c_str());
}

void Layout::end()
{
	ImGui::End();
}

void Layout::endChild()
{
	ImGui::EndChild();
}

void Layout::endCombo()
{
	ImGui::EndCombo();
}

void Layout::endContext()
{
	s_context.pop_back();
}

void Layout::endTreeNode()
{
	ImGui::TreePop();
}

void Layout::hint(const std::string& text)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(text.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void Layout::image(const ImageAssetPtr& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	// Layout::image(image, graphics::TextureRect(), size, size);
}

void Layout::image(const ImageAssetPtr& image, const float width, const float height)
{
	// Layout::image(image, graphics::TextureRect(), width, height);
}

bool Layout::imageButton(const ImageAssetPtr& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	// return Layout::imageButton(image, graphics::TextureRect(), size, size);
	return false;
}

bool Layout::imageButton(const ImageAssetPtr& image, const float width, const float height)
{
	// return Layout::imageButton(image, graphics::TextureRect(), width, height);
	return false;
}

void Layout::input(const std::string& name, int& value)
{
	ImGui::InputInt(id(name).c_str(), &value);
}

void Layout::input(const std::string& name, bool& value)
{
	ImGui::Checkbox(id(name).c_str(), &value);
}

void Layout::input(const std::string& name, float& value)
{
	ImGui::InputFloat(id(name).c_str(), &value);
}

void Layout::input(const std::string& name, double& value)
{
	ImGui::InputDouble(id(name).c_str(), &value);
}

void Layout::input(const std::string& name, std::string& value)
{
	ImGui::InputText(id(name).c_str(), &value);
}

void Layout::inputMultiline(const std::string& name, std::string& value)
{
	ImGui::InputTextMultiline(id(name).c_str(), &value);
}

void Layout::input(const std::string& name, std::filesystem::path& value)
{
	std::string temp = value.string();
	ImGui::InputText(id(name).c_str(), &temp);
	value = temp;
}

void Layout::input(const std::string& name, ImageAssetPtr& value)
{
	// input(name, "Image", (AssetPtr&)value);
}

void Layout::input(const std::string&, math::transform& value)
{
	input("Position", value.position);
	input("Rotation", value.rotation);
	input("Scale", value.scale);
	input("Static", value.isStatic);
}

void Layout::input(const std::string& name, math::vec2& value)
{
	ImGui::InputFloat2(id(name).c_str(), value.data);
}

void Layout::input(const std::string& name, math::vec3& value)
{
	ImGui::InputFloat3(id(name).c_str(), value.data);
}

void Layout::input(const std::string& name, math::vec4& value)
{
	ImGui::InputFloat4(id(name).c_str(), value.data);
}

bool Layout::isKeyDown(const keycode_t keycode)
{
	return ImGui::IsKeyDown(keycode);
}

bool Layout::isKeyPressed(const keycode_t keycode)
{
	return ImGui::IsKeyPressed(keycode);
}

bool Layout::isKeyReleased(const keycode_t keycode)
{
	return ImGui::IsKeyReleased(keycode);
}

bool Layout::isItemHovered()
{
	return ImGui::IsItemHovered();
}

bool Layout::isMouseClicked()
{
	return ImGui::IsMouseClicked(ImGuiMouseButton_Left);
}

bool Layout::isPopupOpen(const std::string& name)
{
	return ImGui::IsPopupOpen(name.c_str());
}

bool Layout::isTreeNodeClicked()
{
	return ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen();
}

bool Layout::isWindowFocused()
{
	return ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
}

bool Layout::isWindowHovered()
{
	return ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
}

void Layout::newLine()
{
	ImGui::NewLine();
}

void Layout::rename(std::string& value)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
	ImGui::SetKeyboardFocusHere(0);
	ImGui::InputText("##rename", &value, ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::PopStyleVar();
}

void Layout::sameLine()
{
	ImGui::SameLine();
}

bool Layout::selectable(const std::string& name, const bool selected)
{
	return ImGui::Selectable(id(name).c_str(), selected);
}

bool Layout::selectable(const std::string& name, bool selected, const std::function<void()>& handler)
{
	if (ImGui::Selectable(id(name).c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			handler();
		}
		return true;
	}
	return false;
}

void Layout::separator()
{
	ImGui::Separator();
}

void Layout::scroll(float position)
{
	ImGui::SetScrollHereY(position);
}

void Layout::scrollToBottom()
{
	scroll(1.f);
}

void Layout::slider(const std::string& name, const int min, const int max, int& value)
{
	ImGui::SliderInt(name.c_str(), &value, min, max);
}

void Layout::slider(const std::string& name, const float min, const float max, float& value)
{
	ImGui::SliderFloat(name.c_str(), &value, min, max);
}

void Layout::setKeyboardFocusHere()
{
	ImGui::SetKeyboardFocusHere();
}

void Layout::text(const std::string& str)
{
	ImGui::Text(str.c_str());
}

void Layout::textWrapped(const std::string& str)
{
	ImGui::TextWrapped(str.c_str());
}

void Layout::title(const std::string& title)
{
	ImGui::Text(title.c_str());
}

void Layout::clear()
{
	for (const auto& pair : s_keyCache)
	{
		delete pair.second;
	}
	s_keyCache.clear();
}

std::string Layout::id(const std::string& label)
{
	if (s_context.empty())
	{
		return label;
	}

	std::string context = "";
	for (const std::string& c : s_context)
	{
		context += (context.empty() ? "" : "_") + c;
	}

	return std::string(label) + "###" + context + "_" + label;
}