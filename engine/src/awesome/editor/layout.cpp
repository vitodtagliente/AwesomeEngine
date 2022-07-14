#include "layout.h"

#include <filesystem>

#include <imgui.h>
#include <imgui_stdlib.h>

#include <awesome/asset/asset_library.h>
#include <awesome/graphics/texture_library.h>

namespace editor
{
	std::string Layout::s_context{};
	std::map<std::string, void*> Layout::s_keyCache{};

	void Layout::begin(const std::string& name)
	{
		ImGui::Begin(id(name).c_str());
	}

	bool Layout::beginCombo(const std::string& name, const std::string& value)
	{
		return ImGui::BeginCombo(id(name).c_str(), value.c_str());
	}

	void Layout::beginContext(const std::string context)
	{
		s_context = context;
	}

	void Layout::beginDrag(const std::string& name, const std::string& item, void* const data, const size_t size)
	{
		ImGuiDragDropFlags src_flags = 0;
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
		//src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
		if (ImGui::BeginDragDropSource(src_flags))
		{
			if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip) && !item.empty())
				ImGui::Text(item.c_str());
			ImGui::SetDragDropPayload(name.c_str(), data, size);
			ImGui::EndDragDropSource();
		}
	}

	bool Layout::button(const std::string& name)
	{
		return ImGui::Button(id(name).c_str());
	}

	bool Layout::button(const std::string& name, const int width, const int height)
	{
		return ImGui::Button(id(name).c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height)));
	}

	bool Layout::collapsingHeader(const std::string& name)
	{
		return ImGui::CollapsingHeader(id(name).c_str());
	}

	void Layout::end()
	{
		ImGui::End();
	}

	void Layout::endCombo()
	{
		ImGui::EndCombo();
	}

	void Layout::endContext()
	{
		s_context.clear();
	}

	void Layout::endDrag(const std::string& name, const std::function<void(void*, size_t)>& handler)
	{
		if (ImGui::BeginDragDropTarget())
		{
			ImGuiDragDropFlags target_flags = 0;
			// target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
			target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(name.c_str(), target_flags))
			{
				handler(payload->Data, payload->DataSize);
			}
			ImGui::EndDragDropTarget();
		}
	}

	void Layout::image(const ImageAssetPtr& image)
	{
		const float size = ImGui::GetContentRegionAvailWidth();
		Layout::image(image, graphics::TextureRect(), size, size);
	}

	void Layout::image(const ImageAssetPtr& image, const float width, const float height)
	{
		Layout::image(image, graphics::TextureRect(), width, height);
	}

	void Layout::image(const ImageAssetPtr& image, const graphics::TextureRect& rect)
	{
		if (image && image->data.has_value())
		{
			const float size = ImGui::GetContentRegionAvailWidth();
			const float width = std::min(size, image->data->width * rect.width * 2);
			const float height = std::min(size, image->data->height * rect.height * 2);
			Layout::image(image, rect, width, height);
		}
	}

	void Layout::image(const ImageAssetPtr& image, const graphics::TextureRect& rect, const float width, const float height)
	{
		if (image != nullptr)
		{
			std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image->descriptor.id);
			if (texture)
			{
				ImGui::Image((void*)(intptr_t)texture->id(), ImVec2(width, height), ImVec2(rect.x, rect.y), ImVec2(rect.x + rect.width, rect.y + rect.height));
			}
		}
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
		ImGui::InputText(name.c_str(), &value);
	}

	void Layout::input(const std::string& name, math::vec2& value)
	{
		ImGui::InputFloat2(id(name).c_str(), value.data);
	}

	void Layout::input(const std::string& name, math::vec3& value)
	{
		ImGui::InputFloat3(id(name).c_str(), value.data);
	}

	void Layout::input(const std::string& name, graphics::Color& value)
	{
		ImGui::ColorEdit4(id(name).c_str(), value.data);
	}

	void Layout::input(const std::string& name, graphics::TextureCoords& value)
	{
		ImGui::InputFloat2(id(name).c_str(), value.data);
	}

	void Layout::input(const std::string& name, graphics::TextureRect& value)
	{
		ImGui::InputFloat4(id(name).c_str(), value.data);
	}

	void Layout::input(const std::string&, SpriteAnimation::Frame& value)
	{
		input("Sprite", value.sprite);
		input("Duration", value.duration);
	}

	bool Layout::isWindowFocused()
	{
		return ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
	}

	bool Layout::isWindowHovered()
	{
		return ImGui::IsWindowHovered();
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

	void Layout::sprite(const SpriteAssetPtr& sprite)
	{
		if (sprite && sprite->data.has_value())
		{
			const Sprite& data = sprite->data.value();
			image(data.image, data.rect);
		}
	}

	void Layout::sprite(const SpriteAssetPtr& sprite, const float width, const float height)
	{
		if (sprite && sprite->data.has_value())
		{
			const Sprite& data = sprite->data.value();
			image(data.image, data.rect, width, height);
		}
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
		return std::string(label) + "###" + s_context + "_" + label;
	}
}