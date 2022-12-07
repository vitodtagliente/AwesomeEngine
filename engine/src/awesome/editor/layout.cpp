#include "layout.h"

#include <filesystem>

#include <imgui.h>
#include <imgui_stdlib.h>

#include <awesome/asset/asset_library.h>
#include <awesome/asset/prefab_asset.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/asset/text_asset.h>
#include <awesome/graphics/texture_library.h>

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

void Layout::input(Type& value)
{
	for (const auto& [name, prop] : value.getTypeProperties())
	{
		if (prop.descriptor.decoratorType != Property::DecoratorType::D_normalized) continue;

		std::string label = name;
		const auto& it = prop.meta.find("Label");
		if (it != prop.meta.end())
		{
			label = !it->second.empty() ? it->second : name;
		}

		switch (prop.descriptor.type)
		{
		case Property::Type::T_bool: input(label, prop.value<bool>()); break;
		case Property::Type::T_char: break;
		case Property::Type::T_double: input(label, prop.value<double>()); break;
		case Property::Type::T_float: input(label, prop.value<float>()); break;
		case Property::Type::T_int: input(label, prop.value<int>()); break;
		case Property::Type::T_void: break;
		case Property::Type::T_custom_enum: input(label, prop.value<int>()); break;
		case Property::Type::T_custom_type:
		{
			// data[name] = ::serialize(prop.value<Type>());
			break;
		}
		case Property::Type::T_container_string: input(label, prop.value<std::string>()); break;
		case Property::Type::T_container_map:
		{

			break;
		}
		case Property::Type::T_container_vector:
		{
			switch (prop.descriptor.children.front().type)
			{
			case Property::Type::T_bool: break;
			case Property::Type::T_char: break;
			case Property::Type::T_double: input(label, prop.value<std::vector<double>>()); break;
			case Property::Type::T_float: input(label, prop.value<std::vector<float>>()); break;
			case Property::Type::T_int: input(label, prop.value<std::vector<int>>()); break;
			case Property::Type::T_void: break;
			case Property::Type::T_custom_enum: input(label, prop.value<std::vector<int>>()); break;
			case Property::Type::T_custom_type:
			{
				switch (prop.descriptor.children.front().decoratorType)
				{
				case Property::DecoratorType::D_shared_ptr: input(label, prop.value<std::vector<std::shared_ptr<Type>>>(), prop.descriptor.children.front().name); break;
				case Property::DecoratorType::D_unique_ptr: input(label, prop.value<std::vector<std::unique_ptr<Type>>>(), prop.descriptor.children.front().name); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				if (prop.descriptor.children.front().children.front().name == "graphics::Color" || prop.descriptor.children.front().children.front().name == "Color")
				{
					input(label, prop.value<std::vector<graphics::Color>>()); break;
				}
				else if (prop.descriptor.children.front().name == "graphics::TextureCoords" || prop.descriptor.children.front().name == "TextureCoords")
				{
					input(label, prop.value<std::vector<graphics::TextureCoords>>()); break;
				}
				else if (prop.descriptor.children.front().name == "graphics::TextureRect" || prop.descriptor.children.front().name == "TextureRect")
				{
					input(label, prop.value<std::vector<graphics::TextureRect>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::transform" || prop.descriptor.children.front().name == "transform")
				{
					input(label, prop.value<std::vector<math::transform>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec4" || prop.descriptor.children.front().name == "vec4" || prop.descriptor.children.front().name == "math::vector4" || prop.descriptor.children.front().name == "vector4")
				{
					input(label, prop.value<std::vector<math::vec4>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec3" || prop.descriptor.children.front().name == "vec3" || prop.descriptor.children.front().name == "math::vector3" || prop.descriptor.children.front().name == "vector3")
				{
					input(label, prop.value<std::vector<math::vec3>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec2" || prop.descriptor.children.front().name == "vec2" || prop.descriptor.children.front().name == "math::vector2" || prop.descriptor.children.front().name == "vector2")
				{
					input(label, prop.value<std::vector<math::vec2>>()); break;
				}
				else if (prop.descriptor.children.front().name == "ImageAssetPtr")
				{
					input(label, prop.value<std::vector<ImageAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "PrefabAssetPtr")
				{
					input(label, prop.value<std::vector<PrefabAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SceneAssetPtr")
				{
					input(label, prop.value<std::vector<SceneAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SpriteAnimationAssetPtr")
				{
					input(label, prop.value<std::vector<SpriteAnimationAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SpriteAssetPtr")
				{
					input(label, prop.value<std::vector<SpriteAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "TextAssetPtr")
				{
					input(label, prop.value<std::vector<TextAssetPtr>>()); break;
				}
				break;
			}
			}
			break;
		}
		case Property::Type::T_unknown:
		default:
		{
			if (prop.descriptor.name == "graphics::Color" || prop.descriptor.name == "Color")
			{
				input(label, prop.value<graphics::Color>());
			}
			else if (prop.descriptor.name == "graphics::TextureCoords" || prop.descriptor.name == "TextureCoords")
			{
				input(label, prop.value<graphics::TextureCoords>());
			}
			else if (prop.descriptor.name == "graphics::TextureRect" || prop.descriptor.name == "TextureRect")
			{
				input(label, prop.value<graphics::TextureRect>());
			}
			else if (prop.descriptor.name == "math::transform" || prop.descriptor.name == "transform")
			{
				input("Position", prop.value<math::transform>());
			}
			else if (prop.descriptor.name == "math::vec4" || prop.descriptor.name == "vec4" || prop.descriptor.name == "math::vector4" || prop.descriptor.name == "vector4")
			{
				Layout::input(label, prop.value<math::vec4>());
			}
			else if (prop.descriptor.name == "math::vec3" || prop.descriptor.name == "vec3" || prop.descriptor.name == "math::vector3" || prop.descriptor.name == "vector3")
			{
				Layout::input(label, prop.value<math::vec3>());
			}
			else if (prop.descriptor.name == "math::vec2" || prop.descriptor.name == "vec2" || prop.descriptor.name == "math::vector2" || prop.descriptor.name == "vector2")
			{
				Layout::input(label, prop.value<math::vec2>());
			}
			else if (prop.descriptor.name == "ImageAssetPtr")
			{
				Layout::input(label, prop.value<ImageAssetPtr>());
			}
			else if (prop.descriptor.name == "PrefabAssetPtr")
			{
				Layout::input(label, prop.value<PrefabAssetPtr>());
			}
			else if (prop.descriptor.name == "SceneAssetPtr")
			{
				Layout::input(label, prop.value<SceneAssetPtr>());
			}
			else if (prop.descriptor.name == "SpriteAnimationAssetPtr")
			{
				Layout::input(label, prop.value<SpriteAnimationAssetPtr>());
			}
			else if (prop.descriptor.name == "SpriteAssetPtr")
			{
				Layout::input(label, prop.value<SpriteAssetPtr>());
			}
			else if (prop.descriptor.name == "TextAssetPtr")
			{
				Layout::input(label, prop.value<TextAssetPtr>());
			}
			break;
		}
		}
	}
}

void Layout::input(std::unique_ptr<Type>& type)
{
	if (type != nullptr)
	{
		input(*type.get());
	}
}

void Layout::input(std::shared_ptr<Type>& type)
{
	if (type != nullptr)
	{
		input(*type.get());
	}
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