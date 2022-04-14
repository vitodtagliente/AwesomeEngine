#include "editor.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/core/reflection.h>
#include <awesome/data/asset_importer.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/color_scheme.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/windows/content_browser_window.h>
#include <awesome/editor/windows/inspector_window.h>
#include <awesome/editor/windows/performance_window.h>
#include <awesome/editor/windows/renderer_window.h>
#include <awesome/editor/windows/scene_window.h>

namespace editor
{
	void Editor::startup()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(Canvas::instance().getHandler()), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		ColorScheme scheme;
		scheme.apply();

		AssetImporter importer;
		importer.import(AssetLibrary::instance().getDirectory(), true);

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

	void Editor::render(graphics::Renderer* const)
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
		m_menu.render();
		for (const auto& window : m_windows)
		{
			Layout::begin(window->getTitle());
			window->setFocus(Layout::isWindowFocused());
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
		Input::instance().preventMouseEvents = ImGui::GetIO().WantCaptureMouse;

		for (const auto& window : m_windows)
		{
			window->update(deltaTime);
		}
	}

	void Editor::registerWindows()
	{
		TypeFactory::load<ContentBrowserWindow>();
		TypeFactory::load<InspectorWindow>();
		TypeFactory::load<PerformanceWindow>();
		TypeFactory::load<RendererWindow>();
		TypeFactory::load<SceneWindow>();

		static std::set<std::string> types = TypeFactory::list("Window");
		for (const std::string& type : types)
		{
			Window* const window = TypeFactory::instantiate<Window>(type);
			if (window)
			{
				m_windows.push_back(std::unique_ptr<Window>(window));
			}

		}
	}
}