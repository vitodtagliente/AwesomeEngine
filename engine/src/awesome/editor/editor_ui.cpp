#include "editor_ui.h"

#include <memory>
#include <sstream>

#include <imgui.h>
#include <imgui_stdlib.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <IconsFontAwesome5.h>

#include <awesome/asset/asset_database.h>
#include <awesome/components/component_library.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/component_inspector.h>
#include <awesome/editor/widgets/asset_browser_dialog.h>
#include <awesome/editor/widgets/save_file_dialog.h>
#include <awesome/engine/input.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

#include "private/component_inspectors/sprite_animator_component_inspector.h"

std::vector<std::string> context;

std::string id(const char* const name)
{
	if (context.empty())
	{
		return name;
	}

	std::string context_id = "";
	for (const std::string& c : context)
	{
		context_id += (context.empty() ? "" : "_") + c;
	}

	return std::string(name) + "###" + context_id + "_" + name;
}

SaveFileDialog saveFileDialog;
std::vector<std::unique_ptr<ComponentInspector>> componentInspectors;

const std::string EditorUI::Icon::copy{ ICON_FA_COPY };
const std::string EditorUI::Icon::cube{ ICON_FA_CUBE };
const std::string EditorUI::Icon::eraser{ ICON_FA_ERASER };
const std::string EditorUI::Icon::eye{ ICON_FA_EYE };
const std::string EditorUI::Icon::file{ ICON_FA_FILE_CODE };
const std::string EditorUI::Icon::folder{ ICON_FA_FOLDER };
const std::string EditorUI::Icon::horse{ ICON_FA_HORSE };
const std::string EditorUI::Icon::image{ ICON_FA_IMAGE };
const std::string EditorUI::Icon::minus{ ICON_FA_MINUS };
const std::string EditorUI::Icon::music{ ICON_FA_MUSIC };
const std::string EditorUI::Icon::paste{ ICON_FA_PASTE };
const std::string EditorUI::Icon::pause{ ICON_FA_PAUSE };
const std::string EditorUI::Icon::play{ ICON_FA_PLAY };
const std::string EditorUI::Icon::plus{ ICON_FA_PLUS };
const std::string EditorUI::Icon::save{ ICON_FA_SAVE };
const std::string EditorUI::Icon::search{ ICON_FA_SEARCH };
const std::string EditorUI::Icon::stop{ ICON_FA_STOP };
const std::string EditorUI::Icon::tree{ ICON_FA_TREE };
const std::string EditorUI::Icon::upload{ ICON_FA_UPLOAD };
const std::string EditorUI::Icon::video{ ICON_FA_VIDEO };

void EditorUI::Child::begin(const char* const name)
{
	ImGui::BeginChild(name, ImVec2(0.f, 0.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
}

void EditorUI::Child::begin(const char* const name, const float width, const float height)
{
	ImGui::BeginChild(name, ImVec2(width, height), false, ImGuiWindowFlags_NoDecoration);
}

void EditorUI::Child::end()
{
	ImGui::EndChild();
}

bool EditorUI::Combo::begin(const char* const name, const char* const value)
{
	return ImGui::BeginCombo(id(name).c_str(), value);
}

void EditorUI::Combo::end()
{
	ImGui::EndCombo();
}

void EditorUI::Dialog::save(const char* const name, const char* const extension, const std::function<void(const std::filesystem::path&)>& handler)
{
	if (saveFileDialog.isOpen()) return;

	saveFileDialog.open(name, extension, handler);
}

void EditorUI::DragDrop::begin(const char* const name, const char* const item, void* const data, const size_t size)
{
	ImGuiDragDropFlags src_flags = 0;
	src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
	src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
	//src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
	if (ImGui::BeginDragDropSource(src_flags))
	{
		if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip) && item != nullptr)
			ImGui::Text(item);
		ImGui::SetDragDropPayload(name, data, size);
		ImGui::EndDragDropSource();
	}
}

void EditorUI::DragDrop::end(const char* const name, const std::function<void(void*, size_t)>& handler)
{
	if (ImGui::BeginDragDropTarget())
	{
		ImGuiDragDropFlags target_flags = 0;
		// target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
		// target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(name, target_flags))
		{
			handler(payload->Data, payload->DataSize);
		}
		ImGui::EndDragDropTarget();
	}
}

void EditorUI::Id::push(const char* const id)
{
	ImGui::PushID(id);
}

void EditorUI::Id::pop()
{
	ImGui::PopID();
}

bool EditorUI::Input::isKeyDown(const keycode_t keycode)
{
	return ImGui::IsKeyDown(static_cast<ImGuiKey>(keycode));
}

bool EditorUI::Input::isKeyPressed(const keycode_t keycode)
{
	return ImGui::IsKeyPressed(static_cast<ImGuiKey>(keycode));
}

bool EditorUI::Input::isKeyReleased(const keycode_t keycode)
{
	return ImGui::IsKeyReleased(static_cast<ImGuiKey>(keycode));
}

bool EditorUI::Input::isItemHovered()
{
	return ImGui::IsItemHovered();
}

bool EditorUI::Input::isMouseClicked()
{
	return ImGui::IsMouseClicked(ImGuiMouseButton_Left);
}

void EditorUI::Input::scroll(const float position)
{
	ImGui::SetScrollHereY(position);
}

void EditorUI::Input::scrollToBottom()
{
	scroll(1.f);
}

bool EditorUI::Menu::beginBar()
{
	return ImGui::BeginMainMenuBar();
}

void EditorUI::Menu::endBar()
{
	ImGui::EndMainMenuBar();
}

bool EditorUI::Menu::begin(const char* const name)
{
	return ImGui::BeginMenu(name);
}

void EditorUI::Menu::end()
{
	ImGui::EndMenu();
}

bool EditorUI::Menu::item(const char* const name)
{
	return ImGui::MenuItem(name);
}

bool EditorUI::Menu::item(const char* const name, bool& checked)
{
	return ImGui::MenuItem(name, nullptr, &checked);
}

bool EditorUI::Popup::begin(const char* const name)
{
	return ImGui::BeginPopup(name);
}

void EditorUI::Popup::end()
{
	ImGui::EndPopup();
}

void EditorUI::Popup::open(const char* const name)
{
	ImGui::OpenPopup(name);
}

void EditorUI::Runtime::startup(void* const windowHandler)
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(windowHandler), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// icons setup
	{
		io.Fonts->AddFontDefault();

		// merge in icons from Font Awesome
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		io.Fonts->AddFontFromFileTTF((std::string("../fonts/") + FONT_ICON_FILE_NAME_FAS).c_str(), 12.0f, &icons_config, icons_ranges);
		// use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid
	}

	// component inspectors setup
	componentInspectors.push_back(std::make_unique<SpriteAnimatorComponentInspector>());

	for (const auto& [name, options] : TypeFactory::list("Type", "ComponentInspector"))
	{
		std::unique_ptr<ComponentInspector> inspector = std::unique_ptr<ComponentInspector>(TypeFactory::instantiate<ComponentInspector>(name));
		if (inspector != nullptr)
		{
			componentInspectors.push_back(std::move(inspector));
		}
	}
}

void EditorUI::Runtime::preRendering()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void EditorUI::Runtime::postRendering()
{
	saveFileDialog.render();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::Runtime::update()
{
	::Input& input = ::Input::instance();
	ImGuiIO& io = ImGui::GetIO();
	input.preventMouseEvents = io.WantCaptureMouse;
	input.preventKeyEvents = io.WantCaptureKeyboard;
}

void EditorUI::Runtime::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool EditorUI::Tree::begin(const char* const name, const bool selected)
{
	return ImGui::TreeNodeEx(name, ImGuiTreeNodeFlags_OpenOnArrow | (selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None));
}

void EditorUI::Tree::end()
{
	ImGui::TreePop();
}

bool EditorUI::Tree::isClicked()
{
	return ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen();
}

void EditorUI::Tree::openNextItem()
{
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
}

void EditorUI::Window::begin(const char* const name)
{
	ImGui::Begin(name);
}

void EditorUI::Window::end()
{
	ImGui::End();
}

bool EditorUI::Window::isFocused()
{
	return ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
}

bool EditorUI::Window::isHovered()
{
	return ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
}

void EditorUI::align(const HorizontalAlignment alignment, const float widthNextElement)
{
	const float regionWidth = ImGui::GetWindowSize().x;

	switch (alignment)
	{
	case HorizontalAlignment::Middle:  ImGui::SetCursorPosX((regionWidth - widthNextElement) / 2); break;
	case HorizontalAlignment::Right: ImGui::SetCursorPosX(regionWidth - widthNextElement); break;
	default:
		break;
	}
}

void EditorUI::begin(const char* const name)
{
	context.push_back(name);
}

bool EditorUI::button(const char* const name)
{
	return ImGui::Button(name);
}

bool EditorUI::button(const char* const name, const float width, const float height)
{
	return ImGui::Button(name, ImVec2(width, height));
}

bool EditorUI::button(const char* const name, const graphics::Color& color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name);
	ImGui::PopStyleColor(3);
	return result;
}

bool EditorUI::button(const char* const name, const graphics::Color& color, const float width, const float height)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name, ImVec2(width, height));
	ImGui::PopStyleColor(3);
	return result;
}

bool EditorUI::collapsingHeader(const char* const name)
{
	return ImGui::CollapsingHeader(id(name).c_str());
}

void EditorUI::end()
{
	if (!context.empty())
		context.pop_back();
}

void EditorUI::hint(const std::string& text)
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

void EditorUI::image(const ImageAsset& image)
{
	const float size = ImGui::GetContentRegionAvail().x;
	EditorUI::image(image, graphics::TextureRect(), size, size);
}

void EditorUI::image(const ImageAsset& image, const float width, const float height)
{
	EditorUI::image(image, graphics::TextureRect(), width, height);
}

void EditorUI::image(const ImageAsset& image, const graphics::TextureRect& rect)
{
	if (image && image.state == Asset::State::Ready)
	{
		const Image& data = *image.resource;
		const float size = ImGui::GetContentRegionAvail().x;
		const float width = std::min(size, data.width * rect.width * 2);
		const float height = std::min(size, data.height * rect.height * 2);
		EditorUI::image(image, rect, width, height);
	}
}

void EditorUI::image(const ImageAsset& image, const graphics::TextureRect& rect, const float width, const float height)
{
	if (image.ready())
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image);
		if (texture)
		{
			ImGui::Image((void*)(intptr_t)texture->id(), ImVec2(width, height), ImVec2(rect.x, rect.y), ImVec2(rect.x + rect.width, rect.y + rect.height));
		}
	}
}

bool EditorUI::imageButton(const ImageAsset& image)
{
	const float size = ImGui::GetContentRegionAvail().x;
	return EditorUI::imageButton(image, graphics::TextureRect(), size, size);
}

bool EditorUI::imageButton(const ImageAsset& image, const float width, const float height)
{
	return EditorUI::imageButton(image, graphics::TextureRect(), width, height);
}

bool EditorUI::imageButton(const ImageAsset& image, const graphics::TextureRect& rect)
{
	if (image.ready())
	{
		const Image& data = *image.resource;
		const float size = ImGui::GetContentRegionAvail().x;
		const float width = std::min(size, data.width * rect.width * 2);
		const float height = std::min(size, data.height * rect.height * 2);
		return EditorUI::imageButton(image, rect, width, height);
	}
	return false;
}

bool EditorUI::imageButton(const ImageAsset& image, const graphics::TextureRect& rect, const float width, const float height)
{
	if (image.ready())
	{
		std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(image);
		if (texture != nullptr)
		{
			return ImGui::ImageButton((void*)(intptr_t)texture->id(), ImVec2(width, height), ImVec2(rect.x, rect.y), ImVec2(rect.x + rect.width, rect.y + rect.height));
		}
	}
	return false;
}

void EditorUI::newLine()
{
	ImGui::NewLine();
}

void EditorUI::rename(std::string& value)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
	ImGui::SetKeyboardFocusHere(0);
	ImGui::InputText("##rename", &value, ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::PopStyleVar();
}

void EditorUI::sameLine()
{
	ImGui::SameLine();
}

bool EditorUI::search(std::string& value)
{
	const std::string previousFilter = value;
	ImGui::PushItemWidth(-1);
	ImGui::InputTextWithHint("filter", Icon::search.c_str(), &value);
	ImGui::PopItemWidth();
	return previousFilter != value;
}

bool EditorUI::selectable(const char* const name, const bool selected)
{
	return ImGui::Selectable(id(name).c_str(), selected);
}

bool EditorUI::selectable(const char* const name, const bool selected, const std::function<void()>& handler)
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

bool EditorUI::selectableDoubleClick(const char* const name, const bool selected)
{
	if (ImGui::Selectable(id(name).c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			return true;
		}
	}
	return false;
}

void EditorUI::separator()
{
	ImGui::Separator();
}

void EditorUI::separatorText(const char* const name)
{
	ImGui::SeparatorText(name);
}

void EditorUI::slider(const char* const name, const int min, const int max, int& value)
{
	ImGui::SliderInt(name, &value, min, max);
}

void EditorUI::slider(const char* const name, const float min, const float max, float& value)
{
	ImGui::SliderFloat(name, &value, min, max);
}

void EditorUI::text(const char* const str)
{
	ImGui::Text(str);
}

void EditorUI::textWrapped(const char* const str)
{
	ImGui::TextWrapped(str);
}

void EditorUI::title(const char* const title)
{
	ImGui::Text(title);
}

math::vec2 EditorUI::windowSize()
{
	const ImVec2 size = ImGui::GetWindowSize();
	return math::vec2(size.x, size.y);
}

void EditorUI::input(const char* const name, Asset& asset)
{
	static AssetBrowserDialog s_assetBrowserDialog;

	std::string label(name);
	label.append(": ");
	if (asset)
	{
		label.append(asset.path.stem().string());
	}

	if (selectable(label.c_str(), false))
	{
		s_assetBrowserDialog.open(name, asset.type, [&asset](const AssetRecord& record) -> void
			{
				asset = record;
				asset.load();
			}
		);
	}
	s_assetBrowserDialog.render(name);
}


void EditorUI::input(const char* const name, int& value)
{
	ImGui::InputInt(id(name).c_str(), &value);
}

void EditorUI::input(const char* const name, bool& value)
{
	ImGui::Checkbox(id(name).c_str(), &value);
}

void EditorUI::input(const char* const name, float& value)
{
	ImGui::InputFloat(id(name).c_str(), &value);
}

void EditorUI::input(const char* const name, double& value)
{
	ImGui::InputDouble(id(name).c_str(), &value);
}

void EditorUI::input(const char* const name, std::string& value)
{
	ImGui::InputText(id(name).c_str(), &value);
}

void EditorUI::input(const char* const name, std::filesystem::path& value)
{
	std::string temp = value.string();
	ImGui::InputText(id(name).c_str(), &temp);
	value = temp;
}

void EditorUI::input(const char* const, math::transform& value)
{
	input("Position", value.position);
	input("Rotation", value.rotation);
	input("Scale", value.scale);
	input("Static", value.isStatic);
}

void EditorUI::input(const char* const name, math::vec2& value)
{
	ImGui::InputFloat2(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, math::vec2i& value)
{
	ImGui::InputInt2(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, math::vec3& value)
{
	ImGui::InputFloat3(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, math::vec3i& value)
{
	ImGui::InputInt3(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, math::vec4& value)
{
	ImGui::InputFloat4(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, math::vec4i& value)
{
	ImGui::InputInt4(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, graphics::Color& value)
{
	ImGui::ColorEdit4(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, graphics::TextureCoords& value)
{
	ImGui::InputFloat2(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, graphics::TextureRect& value)
{
	ImGui::InputFloat4(id(name).c_str(), value.data);
	sameLine();
	begin(name);
	button(Icon::copy.c_str());
	end();

	std::ostringstream s;
	s << std::fixed << std::setprecision(4) << "(" << value.x << "," << value.y << "," << value.width << "," << value.height << ")";
	EditorUI::DragDrop::begin("graphics::TextureRect", s.str().c_str(), (void*)(&value), sizeof(graphics::TextureRect));
	EditorUI::DragDrop::end("graphics::TextureRect", [&value](void* const data, const size_t) -> void { value = *(const graphics::TextureRect*)data; });
}

void EditorUI::inputMultilineText(const char* const name, std::string& value)
{
	ImGui::InputTextMultiline(id(name).c_str(), &value);
}

void EditorUI::input(Entity& entity)
{
	begin("entity");
	button(entity.type_name(), graphics::Color(1.f, .6f, .6f));
	sameLine();
	button(entity.id().value.c_str(), graphics::Color(0.f, .6f, .6f));
	input("Name", entity.name);
	input("Tag", entity.tag);
	input("Position", entity.transform.position);
	input("Rotation", entity.transform.rotation);
	input("Scale", entity.transform.scale);
	input("Persistent", entity.persistent);
	hint("If true, the entity is not destroyed during the loading of a new scene");
	sameLine();
	input("Transient", entity.transient);
	hint("If true, the entity cannot be saved as part of the scene serialization");
	input("Replicate", entity.replicate);
	hint("If true, the entity can be replicated in multiplayer games");
	input("Static", entity.transform.isStatic);
	hint("If true, the entity cannot move. It helps optimizing the transform's computation");
	end();

	static const auto& decorateComponentName = [](const std::string& name) -> std::string
	{
		return StringUtil::replace(name, "Component", "");
	};

	for (const auto& component : entity.components())
	{
		const std::string componentName = component->type_name();
		begin(componentName.c_str());
		if (collapsingHeader(decorateComponentName(componentName).c_str()))
		{
			bool inspected = false;
			for (const std::unique_ptr<ComponentInspector>& inspector : componentInspectors)
			{
				if (inspector->canInspect(*component))
				{
					inspector->inspect(*component);
					inspected = true;
					break;
				}
			}

			if (!inspected)
			{
				input(*component);
			}

			separator();
			if (button((Icon::minus + " Remove Component").c_str()))
			{
				entity.removeComponent(component->getId());
				end();
				break;
			}
		}
		end();
	}

	static const auto& hasComponent = [](const Entity& entity, const std::string& name) -> bool
	{
		const auto& it = std::find_if(
			entity.components().begin(),
			entity.components().end(),
			[&name](const std::unique_ptr<Component>& component) -> bool
			{
				return component->type_name() == name;
			}
		);
		return it != entity.components().end();
	};

	static std::string component_filter;

	align(HorizontalAlignment::Middle, 120.f);
	if (button("Add Component", 120.f))
	{
		Popup::open("Component_Selection_Widget");
		component_filter.clear();
	}

	if (Popup::begin("Component_Selection_Widget"))
	{
		separatorText("Component Browser");
		ComponentLibrary& library = ComponentLibrary::instance();
		for (const ComponentRecord& record : library.records())
		{
			if (hasComponent(entity, record.name)) continue;

			if (selectable(decorateComponentName(record.name).c_str(), false))
			{
				std::unique_ptr<Component> component(record.instantiate());
				if (component)
				{
					entity.addComponent(std::move(component));
					break;
				}
			}
		}
		Popup::end();
	}
}

void EditorUI::input(IType& type)
{
	for (const auto& [name, property] : type.type_properties())
	{
		switch (property.type.type)
		{
		case PropertyType::Type::T_bool: input(name.c_str(), property.value<bool>(&type)); break;
		case PropertyType::Type::T_char: break;
		case PropertyType::Type::T_double: input(name.c_str(), property.value<double>(&type)); break;
		case PropertyType::Type::T_enum: input(name.c_str(), property.value<bool>(&type)); break;
		case PropertyType::Type::T_float: input(name.c_str(), property.value<float>(&type)); break;
		case PropertyType::Type::T_int: input(name.c_str(), property.value<int>(&type)); break;
		case PropertyType::Type::T_native:
		{
			if (property.type.name == reflect::Type<graphics::Color>::name())
			{
				input(name.c_str(), property.value<graphics::Color>(&type));
			}
			else if (property.type.name == reflect::Type<graphics::TextureCoords>::name())
			{
				input(name.c_str(), property.value<graphics::TextureCoords>(&type));
			}
			else if (property.type.name == reflect::Type<graphics::TextureRect>::name())
			{
				input(name.c_str(), property.value<graphics::TextureRect>(&type));
			}
			else if (property.type.name == reflect::Type<math::transform>::name())
			{
				input(name.c_str(), property.value<math::transform>(&type));
			}
			else if (property.type.name == reflect::Type<math::vec2>::name())
			{
				input(name.c_str(), property.value<math::vec2>(&type));
			}
			else if (property.type.name == reflect::Type<math::vec3>::name())
			{
				input(name.c_str(), property.value<math::vec3>(&type));
			}
			else if (property.type.name == reflect::Type<math::vec4>::name())
			{
				input(name.c_str(), property.value<math::vec4>(&type));
			}
			break;
		}
		case PropertyType::Type::T_string: input(name.c_str(), property.value<std::string>(&type)); break;
		case PropertyType::Type::T_template:
		{
			if ((property.type.name == "std::vector" || property.type.name == "vector") && property.type.children.front().type == PropertyType::Type::T_type)
			{
				// const std::string& typeName = property.type.children.front().name;
				// auto& list = property.value<std::vector<IType>&>(&type);

			}
			break;
		}
		case PropertyType::Type::T_type:
		{
			for (const auto& [type_name, options] : TypeFactory::list("Type", "Asset"))
			{
				if (type_name == property.type.name)
				{
					input(name.c_str(), property.value<Asset>(&type));
					break;
				}
			}
			break;
		}
		default:break;
		}
	}
}

void EditorUI::Style::apply(const EditorStyle& editorStyle)
{
	static const auto& toImGuiColor = [](const graphics::Color& color) -> ImVec4
	{
		return ImVec4(color.red, color.green, color.blue, color.alpha);
	};

	ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.5f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 0.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Left;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	const auto activeColor = toImGuiColor(editorStyle.activeColor);
	const auto hoveredColor = toImGuiColor(editorStyle.hoveredColor);

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = activeColor;
	colors[ImGuiCol_FrameBgHovered] = hoveredColor;
	colors[ImGuiCol_FrameBgActive] = activeColor;
	colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
	colors[ImGuiCol_ScrollbarGrab] = activeColor;
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
	colors[ImGuiCol_Button] = activeColor;
	colors[ImGuiCol_ButtonHovered] = hoveredColor;
	colors[ImGuiCol_ButtonActive] = activeColor;
	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
	colors[ImGuiCol_HeaderHovered] = hoveredColor;
	colors[ImGuiCol_HeaderActive] = activeColor;
	colors[ImGuiCol_Separator] = activeColor;
	colors[ImGuiCol_SeparatorHovered] = hoveredColor;
	colors[ImGuiCol_SeparatorActive] = activeColor;
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = hoveredColor;
	colors[ImGuiCol_ResizeGripActive] = activeColor;
	colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_TabHovered] = activeColor;
	colors[ImGuiCol_TabActive] = hoveredColor;
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}