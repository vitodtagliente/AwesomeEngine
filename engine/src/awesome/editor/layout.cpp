#include "layout.h"

#include <filesystem>

#include <imgui.h>
#include <imgui_stdlib.h>

#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/widgets/asset_browser_dialog.h>
#include <awesome/graphics/texture_library.h>

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

bool Layout::beginCombo(const std::string& name, const std::string& value)
{
	return ImGui::BeginCombo(id(name).c_str(), value.c_str());
}

void Layout::beginContext(const std::string context)
{
	s_context.push_back(context);
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
	Layout::image(image, graphics::TextureRect(), size, size);
}

void Layout::image(const ImageAssetPtr& image, const float width, const float height)
{
	Layout::image(image, graphics::TextureRect(), width, height);
}

void Layout::image(const ImageAssetPtr& image, const graphics::TextureRect& rect)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		const float size = ImGui::GetContentRegionAvailWidth();
		const float width = std::min(size, image->data.width * rect.width * 2);
		const float height = std::min(size, image->data.height * rect.height * 2);
		Layout::image(image, rect, width, height);
	}
}

void Layout::image(const ImageAssetPtr& image, const graphics::TextureRect& rect, const float width, const float height)
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

bool Layout::imageButton(const ImageAssetPtr& image)
{
	const float size = ImGui::GetContentRegionAvailWidth();
	return Layout::imageButton(image, graphics::TextureRect(), size, size);
}

bool Layout::imageButton(const ImageAssetPtr& image, const float width, const float height)
{
	return Layout::imageButton(image, graphics::TextureRect(), width, height);
}

bool Layout::imageButton(const ImageAssetPtr& image, const graphics::TextureRect& rect)
{
	if (image != nullptr && image->state == Asset::State::Ready)
	{
		const float size = ImGui::GetContentRegionAvailWidth();
		const float width = std::min(size, image->data.width * rect.width * 2);
		const float height = std::min(size, image->data.height * rect.height * 2);
		return Layout::imageButton(image, rect, width, height);
	}
	return false;
}

bool Layout::imageButton(const ImageAssetPtr& image, const graphics::TextureRect& rect, const float width, const float height)
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

void Layout::input(const std::string& name, const std::string& type, AssetPtr& value)
{
	static AssetBrowserDialog s_assetBrowserDialog;

	if (Layout::selectable(name + ": " + (value ? value->path.stem().string() : ""), false))
	{
		s_assetBrowserDialog.open(name, type, [&value](const AssetPtr& asset) -> void
			{
				value = asset;
			}
		);
	}
	s_assetBrowserDialog.render(name);
}

void Layout::input(const std::string& name, ImageAssetPtr& value)
{
	input(name, "Image", (AssetPtr&)value);
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

void Layout::input(const std::string& name, const std::string& category, TypeName<Type>& type)
{
	if (Layout::beginCombo(name, type.value))
	{
		const std::vector<TypeDefinition>& s_types = TypeFactory::list("Type", category);
		for (const TypeDefinition& s_type : s_types)
		{
			if (Layout::selectable(s_type.name.c_str(), false))
			{
				type.value = s_type.name;
				Layout::endCombo();
				return; // force the refresh of the inspector
			}
		}
		Layout::endCombo();
	}
}

void Layout::input(Type& value)
{
	beginContext(value.getTypeName());

	for (const auto& [name, prop] : value.getTypeProperties())
	{
		if (prop.descriptor.type == Property::Type::T_custom_type)
		{
			switch (prop.descriptor.decoratorType)
			{
			case Property::DecoratorType::D_shared_ptr: input(name, prop.value<std::shared_ptr<Type>>(), prop.descriptor.name); break;
			case Property::DecoratorType::D_unique_ptr: input(name, prop.value<std::unique_ptr<Type>>(), prop.descriptor.name); break;
			default:break;
			}
		}

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
		case Property::Type::T_custom_enum: input(label, prop.value<int>(), EnumFactory::definition(prop.descriptor.name)); break;
		case Property::Type::T_custom_type:
		{

			break;
		}
		case Property::Type::T_container_string: input(label, prop.value<std::string>()); break;
		case Property::Type::T_container_map:
		{
			if (prop.descriptor.children.front().type != Property::Type::T_container_string)
			{
				// string keys only are supported
				break;
			}

			switch (prop.descriptor.children.back().type)
			{
			case Property::Type::T_bool: input(label, prop.value<std::map<std::string, bool>>()); break;
			case Property::Type::T_char: break;
			case Property::Type::T_double: input(label, prop.value<std::map<std::string, double>>()); break;
			case Property::Type::T_float: input(label, prop.value<std::map<std::string, float>>()); break;
			case Property::Type::T_int: input(label, prop.value<std::map<std::string, int>>()); break;
			case Property::Type::T_void: break;
			case Property::Type::T_custom_enum: input(label, prop.value<std::map<std::string, int>>()); break;
			case Property::Type::T_custom_type:
			{
				switch (prop.descriptor.children.back().decoratorType)
				{
				case Property::DecoratorType::D_shared_ptr: input(label, prop.value<std::map<std::string, std::shared_ptr<Type>>>(), prop.descriptor.children.back().name); break;
				case Property::DecoratorType::D_unique_ptr: input(label, prop.value<std::map<std::string, std::unique_ptr<Type>>>(), prop.descriptor.children.back().name); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				const std::string& backChildTypeName = prop.descriptor.children.back().name;
				if (backChildTypeName == "graphics::Color" || backChildTypeName == "Color")
				{
					input(label, prop.value<std::map<std::string, graphics::Color>>()); break;
				}
				else if (backChildTypeName == "graphics::TextureCoords" || backChildTypeName == "TextureCoords")
				{
					input(label, prop.value<std::map<std::string, graphics::TextureCoords>>()); break;
				}
				else if (backChildTypeName == "graphics::TextureRect" || backChildTypeName == "TextureRect")
				{
					input(label, prop.value<std::map<std::string, graphics::TextureRect>>()); break;
				}
				else if (backChildTypeName == "math::transform" || backChildTypeName == "transform")
				{
					input(label, prop.value<std::map<std::string, math::transform>>()); break;
				}
				else if (backChildTypeName == "math::vec4" || backChildTypeName == "vec4" || backChildTypeName == "math::vector4" || backChildTypeName == "vector4")
				{
					input(label, prop.value<std::map<std::string, math::vec4>>()); break;
				}
				else if (backChildTypeName == "math::vec3" || backChildTypeName == "vec3" || backChildTypeName == "math::vector3" || backChildTypeName == "vector3")
				{
					input(label, prop.value<std::map<std::string, math::vec3>>()); break;
				}
				else if (backChildTypeName == "math::vec2" || backChildTypeName == "vec2" || backChildTypeName == "math::vector2" || backChildTypeName == "vector2")
				{
					input(label, prop.value<std::map<std::string, math::vec2>>()); break;
				}
				else if (StringUtil::contains(backChildTypeName, "AssetPtr"))
				{
					input(label, StringUtil::replace(prop.descriptor.name, "Ptr", ""), prop.value<std::map<std::string, AssetPtr>>()); break;
				}
				break;
			}
			}
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
				const std::string& frontChildTypeName = prop.descriptor.children.front().name;
				if (frontChildTypeName == "graphics::Color" || frontChildTypeName == "Color")
				{
					input(label, prop.value<std::vector<graphics::Color>>()); break;
				}
				else if (frontChildTypeName == "graphics::TextureCoords" || frontChildTypeName == "TextureCoords")
				{
					input(label, prop.value<std::vector<graphics::TextureCoords>>()); break;
				}
				else if (frontChildTypeName == "graphics::TextureRect" || frontChildTypeName == "TextureRect")
				{
					input(label, prop.value<std::vector<graphics::TextureRect>>()); break;
				}
				else if (frontChildTypeName == "math::transform" || frontChildTypeName == "transform")
				{
					input(label, prop.value<std::vector<math::transform>>()); break;
				}
				else if (frontChildTypeName == "math::vec4" || frontChildTypeName == "vec4" || frontChildTypeName == "math::vector4" || frontChildTypeName == "vector4")
				{
					input(label, prop.value<std::vector<math::vec4>>()); break;
				}
				else if (frontChildTypeName == "math::vec3" || frontChildTypeName == "vec3" || frontChildTypeName == "math::vector3" || frontChildTypeName == "vector3")
				{
					input(label, prop.value<std::vector<math::vec3>>()); break;
				}
				else if (frontChildTypeName == "math::vec2" || frontChildTypeName == "vec2" || frontChildTypeName == "math::vector2" || frontChildTypeName == "vector2")
				{
					input(label, prop.value<std::vector<math::vec2>>()); break;
				}
				else if (StringUtil::contains(frontChildTypeName, "AssetPtr"))
				{
					input(label, StringUtil::replace(prop.descriptor.name, "Ptr", ""), prop.value<std::vector<AssetPtr>>()); break;
				}
				break;
			}
			}
			break;
		}
		case Property::Type::T_unknown:
		default:
		{
			if (prop.descriptor.name == "std::filesystem::path")
			{
				input(label, prop.value<std::filesystem::path>());
			}
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
			else if (StringUtil::contains(prop.descriptor.name, "AssetPtr"))
			{
				Layout::input(label, StringUtil::replace(prop.descriptor.name, "Ptr", ""), prop.value<AssetPtr>());
			}
			else if (StringUtil::startsWith(prop.descriptor.name, "TypeName"))
			{
				Layout::input(label, prop.descriptor.children.front().name, prop.value<TypeName<Type>>());
			}
			break;
		}
		}
	}

	endContext();
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

void Layout::input(const std::string& name, std::unique_ptr<Type>& type, const std::string& typeName)
{
	if (type == nullptr)
	{
		type = std::unique_ptr<Type>(TypeFactory::instantiate(typeName));
	}
	if (collapsingHeader(name))
	{
		input(type);
	}
}

void Layout::input(const std::string& name, std::shared_ptr<Type>& type, const std::string& typeName)
{
	if (type == nullptr)
	{
		type = std::shared_ptr<Type>(TypeFactory::instantiate(typeName));
	}
	if (collapsingHeader(name))
	{
		input(type);
	}
}

void Layout::input(const std::string& name, const std::string& type, std::vector<AssetPtr>& list)
{
	input<AssetPtr>(
		name,
		list,
		[type](AssetPtr& element) -> void
		{
			input("Value", type, element);
		},
		[]() -> AssetPtr
		{
			return AssetPtr();
		}
		);
}

void Layout::input(const std::string& name, std::vector<std::shared_ptr<Type>>& list, const std::string& typeName)
{
	input<std::shared_ptr<Type>>(
		name,
		list,
		[](std::shared_ptr<Type>& element) -> void
		{
			input(element);
		},
		[typeName]() -> std::shared_ptr<Type>
		{
			return std::shared_ptr<Type>(TypeFactory::instantiate(typeName));
		}
		);
}

void Layout::input(const std::string& name, std::vector<std::unique_ptr<Type>>& list, const std::string& typeName)
{
	input<std::unique_ptr<Type>>(
		name,
		list,
		[](std::unique_ptr<Type>& element) -> void
		{
			input(element);
		},
		[typeName]() -> std::unique_ptr<Type>
		{
			return std::unique_ptr<Type>(TypeFactory::instantiate(typeName));
		}
		);
}

void Layout::input(const std::string& name, const std::string& type, std::map<std::string, AssetPtr>& map)
{
	input<std::string, AssetPtr>(
		name,
		map,
		[type](AssetPtr& element) -> void
		{
			input("Value", type, element);
		},
		[]() -> AssetPtr
		{
			return AssetPtr();
		}
		);
}

void Layout::input(const std::string& name, std::map<std::string, std::shared_ptr<Type>>& map, const std::string& typeName)
{
	input<std::string, std::shared_ptr<Type>>(
		name,
		map,
		[](std::shared_ptr<Type>& element) -> void
		{
			input(element);
		},
		[typeName]() -> std::shared_ptr<Type>
		{
			return std::shared_ptr<Type>(TypeFactory::instantiate(typeName));
		}
		);
}

void Layout::input(const std::string& name, std::map<std::string, std::unique_ptr<Type>>& map, const std::string& typeName)
{
	input<std::string, std::unique_ptr<Type>>(
		name,
		map,
		[](std::unique_ptr<Type>& element) -> void
		{
			input(element);
		},
		[typeName]() -> std::unique_ptr<Type>
		{
			return std::unique_ptr<Type>(TypeFactory::instantiate(typeName));
		}
		);
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