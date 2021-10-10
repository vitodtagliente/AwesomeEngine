#include "context.h"

#include <imgui.h>

namespace editor
{
	Context::Context()
	{

	}

	bool Context::collapsingHeader(const std::string& name)
	{
		return ImGui::CollapsingHeader(name.c_str());
	}

	void Context::input(const std::string& name, int* value)
	{
		ImGui::InputInt(name.c_str(), value);
	}

	void Context::input(const std::string& name, bool* value)
	{
		ImGui::Checkbox(name.c_str(), value);
	}

	void Context::input(const std::string& name, float* value)
	{
		ImGui::InputFloat(name.c_str(), value);
	}

	void Context::input(const std::string& name, std::string* value, const size_t size)
	{
		ImGui::InputText(name.c_str(), const_cast<char*>(value->c_str()), size);
	}

	void Context::input(const std::string& name, math::vec2* value)
	{
		ImGui::InputFloat2(name.c_str(), value->data);
	}

	void Context::input(const std::string& name, math::vec3* value)
	{
		ImGui::InputFloat3(name.c_str(), value->data);
	}

	void Context::input(const std::string& name, graphics::Color* value)
	{
		ImGui::ColorEdit4(name.c_str(), value->data);
	}

	void Context::input(const std::string& name, graphics::TextureCoords* value)
	{
		ImGui::InputFloat2(name.c_str(), value->data);
	}

	void Context::input(const std::string& name, graphics::TextureRect* value)
	{
		ImGui::InputFloat4(name.c_str(), value->data);
	}
	
	bool Context::selectable(const std::string& name, const bool selected)
	{
		return ImGui::Selectable(name.c_str(), selected);
	}

	void Context::text(const std::string& str)
	{
		ImGui::Text(str.c_str());
	}
}