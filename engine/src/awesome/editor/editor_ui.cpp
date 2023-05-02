#include "editor_ui.h"

#include <imgui.h>
#include <imgui_stdlib.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <IconsFontAwesome5.h>

#include <awesome/asset/asset_database.h>
#include <awesome/editor/widgets/asset_browser_dialog.h>
#include <awesome/engine/input.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

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
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::Runtime::update()
{
	Input& input = Input::instance();
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

void EditorUI::begin(const char* const name)
{
	context.push_back(name);
}

void EditorUI::beginChild(const char* const name)
{
	ImGui::BeginChild(name, ImVec2(0.f, 0.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
}

void EditorUI::beginChild(const char* const name, const float width, const float height)
{
	ImGui::BeginChild(name, ImVec2(width, height), false, ImGuiWindowFlags_NoDecoration);
}

bool EditorUI::beginCombo(const char* const name, const char* const value)
{
	return ImGui::BeginCombo(id(name).c_str(), value);
}

bool EditorUI::button(const char* const name)
{
	return ImGui::Button(name);
}

bool EditorUI::button(const char* const name, const int width, const int height)
{
	return ImGui::Button(name, ImVec2(static_cast<float>(width), static_cast<float>(height)));
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

bool EditorUI::button(const char* const name, const graphics::Color& color, const int width, const int height)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.red, color.green, color.blue, color.alpha));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.red, color.green, color.blue + 0.1f, color.alpha + 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.red, color.green, color.blue + 0.2f, color.alpha + 0.2f));
	const bool result = ImGui::Button(name, ImVec2(static_cast<float>(width), static_cast<float>(height)));
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

void EditorUI::endChild()
{
	ImGui::EndChild();
}

void EditorUI::endCombo()
{
	ImGui::EndCombo();
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
	const float size = ImGui::GetContentRegionAvailWidth();
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
		const float size = ImGui::GetContentRegionAvailWidth();
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
	const float size = ImGui::GetContentRegionAvailWidth();
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
		const float size = ImGui::GetContentRegionAvailWidth();
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

bool EditorUI::selectable(const char* const name, bool selected, const std::function<void()>& handler)
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

void EditorUI::separator()
{
	ImGui::Separator();
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

void EditorUI::input(const char* const name, math::vec3& value)
{
	ImGui::InputFloat3(id(name).c_str(), value.data);
}

void EditorUI::input(const char* const name, math::vec4& value)
{
	ImGui::InputFloat4(id(name).c_str(), value.data);
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
}

void EditorUI::inputMultilineText(const char* const name, std::string& value)
{
	ImGui::InputTextMultiline(id(name).c_str(), &value);
}