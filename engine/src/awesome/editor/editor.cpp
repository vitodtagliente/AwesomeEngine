#include "editor.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <IconsFontAwesome5.h>

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/entity/entity.h>

#include "color_scheme.h"
#include "dialog.h"
#include "layout.h"

#include "windows/windows.h"

void Editor::startup()
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

	m_menu.init();

	registerWindows();
	for (const auto& window : m_windows)
	{
		window->init();
	}
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

void Editor::render(graphics::Renderer2D* const)
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	m_menu.render();
	if (settings.renderWindows)
	{
		for (const auto& window : m_windows)
		{
			Layout::begin(window->getTitle());
			window->setFocus(Layout::isWindowFocused());
			window->render();
			Layout::end();
		}
	}

	Dialog::instance().render();
}

void Editor::postRendering()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::update(const double deltaTime)
{
	Input::instance().preventMouseEvents = ImGui::GetIO().WantCaptureMouse;

	for (const auto& window : m_windows)
	{
		window->update(deltaTime);
	}
}

void Editor::registerWindows()
{
	static std::vector<std::string> types = TypeFactory::list("Category", "Window");
	for (const std::string& type : types)
	{
		Window* const window = TypeFactory::instantiate<Window>(type);
		if (window != nullptr)
		{
			m_windows.push_back(std::unique_ptr<Window>(window));
		}
	}
}

void Editor::State::select(const AssetPtr& asset)
{
	if (selection.asset == asset) return;

	static const size_t s_maxHistory{ 10 };

	selection.asset = asset;
	if (history.size() == s_maxHistory)
	{
		history.pop();
	}
	history.push(asset);
	Layout::clear();

	onSelectedAssetChanged.broadcast(asset);
}

void Editor::State::select(Entity* const entity)
{
	if (selection.entity == entity) return;

	selection.entity = entity;
	Layout::clear();

	onSelectedEntityChanged.broadcast(entity);
}

void Editor::State::select(const std::filesystem::path& folder)
{
	if (folder == path) return;

	path = folder;
	onSelectedPathChanged.broadcast(folder);
}

void Editor::State::unselectAsset()
{
	selection.asset = nullptr;
}

void Editor::State::unselectEntity()
{
	selection.entity = nullptr;
}