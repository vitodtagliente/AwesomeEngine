#include "layout.h"

#include <imgui.h>

#include <awesome/graphics/texture_library.h>

namespace editor
{
	void Layout::begin(const std::string& name)
	{
		ImGui::Begin(name.c_str());
	}

	bool Layout::beginCombo(const std::string& name)
	{
		return ImGui::BeginCombo(name.c_str(), "");
	}

	bool Layout::button(const std::string& name)
	{
		return ImGui::Button(name.c_str());
	}

	bool Layout::button(const std::string& name, const int width, const int height)
	{
		return ImGui::Button(name.c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height)));
	}

	bool Layout::collapsingHeader(const std::string& name)
	{
		return ImGui::CollapsingHeader(name.c_str());
	}

	void Layout::end()
	{
		ImGui::End();
	}

	void Layout::endCombo()
	{
		ImGui::EndCombo();
	}

	void Layout::image(const std::shared_ptr<ImageAsset>& image)
	{
		if (image != nullptr)
		{
			std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance()->find(image->id);
			if (texture)
			{
				ImGui::Image((void*)(intptr_t)texture->id(), ImVec2(256, 256));
			}
		}
	}

	void Layout::input(const std::string& name, int* value)
	{
		ImGui::InputInt(name.c_str(), value);
	}

	void Layout::input(const std::string& name, bool* value)
	{
		ImGui::Checkbox(name.c_str(), value);
	}

	void Layout::input(const std::string& name, float* value)
	{
		ImGui::InputFloat(name.c_str(), value);
	}

	void Layout::input(const std::string& name, std::string* value, const size_t size)
	{
		ImGui::InputText(name.c_str(), const_cast<char*>(value->c_str()), size);
	}

	void Layout::input(const std::string& name, vec2* value)
	{
		ImGui::InputFloat2(name.c_str(), value->data);
	}

	void Layout::input(const std::string& name, vec3* value)
	{
		ImGui::InputFloat3(name.c_str(), value->data);
	}

	void Layout::input(const std::string& name, graphics::Color* value)
	{
		ImGui::ColorEdit4(name.c_str(), value->data);
	}

	void Layout::input(const std::string& name, graphics::TextureCoords* value)
	{
		ImGui::InputFloat2(name.c_str(), value->data);
	}

	void Layout::input(const std::string& name, graphics::TextureRect* value)
	{
		ImGui::InputFloat4(name.c_str(), value->data);
	}

	void Layout::newLine()
	{
		ImGui::NewLine();
	}

	void Layout::sameLine()
	{
		ImGui::SameLine();
	}

	bool Layout::selectable(const std::string& name, const bool selected)
	{
		return ImGui::Selectable(name.c_str(), selected);
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

	void Layout::text(const std::string& str)
	{
		ImGui::Text(str.c_str());
	}

	void Layout::textWrapped(const std::string& str)
	{
		ImGui::TextWrapped(str.c_str());
	}
}