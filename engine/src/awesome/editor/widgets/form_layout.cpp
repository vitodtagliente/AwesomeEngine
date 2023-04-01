#include "form_layout.h"

#include <imgui.h>
#include <imgui_stdlib.h>

#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

std::vector<std::string> FormLayout::s_context;

void FormLayout::begin(const char* const name)
{
	s_context.push_back(name);
}

void FormLayout::beginChild(const char* const name)
{
	ImGui::BeginChild(name, ImVec2(0.f, 0.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
}

void FormLayout::beginChild(const char* const name, const float width, const float height)
{
	ImGui::BeginChild(name, ImVec2(width, height), false, ImGuiWindowFlags_NoDecoration);
}

bool FormLayout::beginCombo(const char* const name, const char* const value)
{
	return ImGui::BeginCombo(id(name).c_str(), value);
}

bool FormLayout::button(const char* const name)
{
	return ImGui::Button(name);
}

bool FormLayout::button(const char* const name, const int width, const int height)
{
	return ImGui::Button(name, ImVec2(static_cast<float>(width), static_cast<float>(height)));
}

bool FormLayout::button(const char* const name, const graphics::Color& color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name);
	ImGui::PopStyleColor(3);
	return result;
}

bool FormLayout::button(const char* const name, const graphics::Color& color, const int width, const int height)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name, ImVec2(static_cast<float>(width), static_cast<float>(height)));
	ImGui::PopStyleColor(3);
	return result;
}

bool FormLayout::collapsingHeader(const char* const name)
{
	return ImGui::CollapsingHeader(id(name).c_str());
}

void FormLayout::end()
{
	if (!s_context.empty())
		s_context.pop_back();
}

void FormLayout::endChild()
{
	ImGui::EndChild();
}

void FormLayout::endCombo()
{
	ImGui::EndCombo();
}

void FormLayout::hint(const std::string& text)
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

void FormLayout::image(const std::shared_ptr<ImageAsset>& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	FormLayout::image(image, graphics::TextureRect(), size, size);
}

void FormLayout::image(const std::shared_ptr<ImageAsset>& image, const float width, const float height)
{
	FormLayout::image(image, graphics::TextureRect(), width, height);
}

void FormLayout::image(const std::shared_ptr<ImageAsset>& image, const graphics::TextureRect& rect)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		const float size = ImGui::GetContentRegionAvailWidth();
		const float width = std::min(size, image->data.width * rect.width * 2);
		const float height = std::min(size, image->data.height * rect.height * 2);
		FormLayout::image(image, rect, width, height);
	}
}

void FormLayout::image(const std::shared_ptr<ImageAsset>& image, const graphics::TextureRect& rect, const float width, const float height)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image->id);
		if (texture)
		{
			ImGui::Image((void*)(intptr_t)texture->id(), ImVec2(width, height), ImVec2(rect.x, rect.y), ImVec2(rect.x + rect.width, rect.y + rect.height));
		}
	}
}

bool FormLayout::imageButton(const std::shared_ptr<ImageAsset>& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	return FormLayout::imageButton(image, graphics::TextureRect(), size, size);
}

bool FormLayout::imageButton(const std::shared_ptr<ImageAsset>& image, const float width, const float height)
{
	return FormLayout::imageButton(image, graphics::TextureRect(), width, height);
}

bool FormLayout::imageButton(const std::shared_ptr<ImageAsset>& image, const graphics::TextureRect& rect)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		const float size = ImGui::GetContentRegionAvailWidth();
		const float width = std::min(size, image->data.width * rect.width * 2);
		const float height = std::min(size, image->data.height * rect.height * 2);
		return FormLayout::imageButton(image, rect, width, height);
	}
	return false;
}

bool FormLayout::imageButton(const std::shared_ptr<ImageAsset>& image, const graphics::TextureRect& rect, const float width, const float height)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image->id);
		if (texture != nullptr)
		{
			return ImGui::ImageButton((void*)(intptr_t)texture->id(), ImVec2(width, height), ImVec2(rect.x, rect.y), ImVec2(rect.x + rect.width, rect.y + rect.height));
		}
	}
	return false;
}

void FormLayout::input(const char* const name, int& value)
{
	ImGui::InputInt(id(name).c_str(), &value);
}

void FormLayout::input(const char* const name, bool& value)
{
	ImGui::Checkbox(id(name).c_str(), &value);
}

void FormLayout::input(const char* const name, float& value)
{
	ImGui::InputFloat(id(name).c_str(), &value);
}

void FormLayout::input(const char* const name, double& value)
{
	ImGui::InputDouble(id(name).c_str(), &value);
}

void FormLayout::input(const char* const name, std::string& value)
{
	ImGui::InputText(id(name).c_str(), &value);
}

void FormLayout::inputMultiline(const char* const name, std::string& value)
{
	ImGui::InputTextMultiline(id(name).c_str(), &value);
}

void FormLayout::input(const char* const name, std::filesystem::path& value)
{
	std::string temp = value.string();
	ImGui::InputText(id(name).c_str(), &temp);
	value = temp;
}

void FormLayout::input(const char* const, math::transform& value)
{
	input("Position", value.position);
	input("Rotation", value.rotation);
	input("Scale", value.scale);
	input("Static", value.isStatic);
}

void FormLayout::input(const char* const name, math::vec2& value)
{
	ImGui::InputFloat2(id(name).c_str(), value.data);
}

void FormLayout::input(const char* const name, math::vec3& value)
{
	ImGui::InputFloat3(id(name).c_str(), value.data);
}

void FormLayout::input(const char* const name, math::vec4& value)
{
	ImGui::InputFloat4(id(name).c_str(), value.data);
}

void FormLayout::input(const char* const name, graphics::Color& value)
{
	ImGui::ColorEdit4(id(name).c_str(), value.data);
}

void FormLayout::input(const char* const name, graphics::TextureCoords& value)
{
	ImGui::InputFloat2(id(name).c_str(), value.data);
}

void FormLayout::input(const char* const name, graphics::TextureRect& value)
{
	ImGui::InputFloat4(id(name).c_str(), value.data);
}

void FormLayout::newLine()
{
	ImGui::NewLine();
}

void FormLayout::sameLine()
{
	ImGui::SameLine();
}

bool FormLayout::selectable(const char* const name, const bool selected)
{
	return ImGui::Selectable(id(name).c_str(), selected);
}

bool FormLayout::selectable(const char* const name, bool selected, const std::function<void()>& handler)
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

void FormLayout::separator()
{
	ImGui::Separator();
}

void FormLayout::slider(const char* const name, const int min, const int max, int& value)
{
	ImGui::SliderInt(name, &value, min, max);
}

void FormLayout::slider(const char* const name, const float min, const float max, float& value)
{
	ImGui::SliderFloat(name, &value, min, max);
}

void FormLayout::text(const char* const str)
{
	ImGui::Text(str);
}

void FormLayout::textWrapped(const char* const str)
{
	ImGui::TextWrapped(str);
}

void FormLayout::title(const char* const title)
{
	ImGui::Text(title);
}

std::string FormLayout::id(const char* const name)
{
	if (s_context.empty())
	{
		return name;
	}

	std::string context = "";
	for (const std::string& c : s_context)
	{
		context += (context.empty() ? "" : "_") + c;
	}

	return std::string(name) + "###" + context + "_" + name;
}