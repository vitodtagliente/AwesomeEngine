#include "editor.h"

#include <assert.h>

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <IconsFontAwesome5.h>

#include <awesome/asset/asset_library.h>
#include <awesome/engine/canvas.h>
#include <awesome/engine/input.h>
#include <awesome/scene/entity.h>

#include "color_scheme.h"
#include "layout.h"

#include "windows/asset_inspector_window.h"
#include "windows/content_browser_window.h"
#include "windows/entity_inspector_window.h"
#include "windows/scene_window.h"

Editor* Editor::s_instance{ nullptr };

Editor::Editor()
	: EngineModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

bool Editor::startup()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(Canvas::instance().getHandler()), true);
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

	ColorScheme scheme;
	scheme.apply();

	registerWindows();
	for (const auto& window : m_windows)
	{
		window->init();
	}

	return true;
}

void Editor::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Editor::preRendering()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Editor::render()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

	for (const auto& window : m_windows)
	{
		if (!window->visible) continue;

		Layout::begin(window->getTitle());
		window->setFocus(Layout::isWindowFocused());
		window->setIsHovered(Layout::isWindowHovered());
		window->render();
		Layout::end();
	}
}

void Editor::postRendering()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::update(const double deltaTime)
{
	Input& input = Input::instance();
	ImGuiIO& io = ImGui::GetIO();
	input.preventMouseEvents = io.WantCaptureMouse;
	input.preventKeyEvents = io.WantCaptureKeyboard;

	for (const auto& window : m_windows)
	{
		window->update(deltaTime);
	}
}

void Editor::registerWindows()
{
	registerWindow<AssetInspectorWindow>();
	registerWindow<ContentBrowserWindow>();
	registerWindow<EntityInspectorWindow>();
	registerWindow<SceneWindow>();
}