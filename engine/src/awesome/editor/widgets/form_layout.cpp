#include "form_layout.h"

#include <imgui.h>

#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

bool FormLayout::button(char* const name)
{
	return ImGui::Button(name);
}

bool FormLayout::button(char* const name, const int width, const int height)
{
	return ImGui::Button(name, ImVec2(static_cast<float>(width), static_cast<float>(height)));
}

bool FormLayout::button(char* const name, const graphics::Color& color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name);
	ImGui::PopStyleColor(3);
	return result;
}

bool FormLayout::button(char* const name, const graphics::Color& color, const int width, const int height)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name, ImVec2(static_cast<float>(width), static_cast<float>(height)));
	ImGui::PopStyleColor(3);
	return result;
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

void FormLayout::image(const ImageAssetPtr& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	FormLayout::image(image, graphics::TextureRect(), size, size);
}

void FormLayout::image(const ImageAssetPtr& image, const float width, const float height)
{
	FormLayout::image(image, graphics::TextureRect(), width, height);
}

void FormLayout::image(const ImageAssetPtr& image, const graphics::TextureRect& rect)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		const float size = ImGui::GetContentRegionAvailWidth();
		const float width = std::min(size, image->data.width * rect.width * 2);
		const float height = std::min(size, image->data.height * rect.height * 2);
		FormLayout::image(image, rect, width, height);
	}
}

void FormLayout::image(const ImageAssetPtr& image, const graphics::TextureRect& rect, const float width, const float height)
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

bool FormLayout::imageButton(const ImageAssetPtr& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	return FormLayout::imageButton(image, graphics::TextureRect(), size, size);
}

bool FormLayout::imageButton(const ImageAssetPtr& image, const float width, const float height)
{
	return FormLayout::imageButton(image, graphics::TextureRect(), width, height);
}

bool FormLayout::imageButton(const ImageAssetPtr& image, const graphics::TextureRect& rect)
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

bool FormLayout::imageButton(const ImageAssetPtr& image, const graphics::TextureRect& rect, const float width, const float height)
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