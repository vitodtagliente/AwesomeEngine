#include "editor.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/application/input.h>
#include <awesome/core/reflection.h>
#include <awesome/data/asset_library.h>

#include "asset_importer.h"
#include "color_scheme.h"
#include "layout.h"
#include "window.h"

#include <awesome/editor/windows/content_browser.h>
#include <awesome/editor/windows/inspector_window.h>
#include <awesome/editor/windows/performance.h>
#include <awesome/editor/windows/renderer_inspector.h>
#include <awesome/editor/windows/scene_inspector.h>

namespace editor
{
	Editor::Editor()
		: m_windows()
	{
	}

	void Editor::startup()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(Canvas::instance()->getHandler()), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		// https://coolors.co/252131-f4f1de-da115e-792359-c7ef00
		ColorScheme scheme(0x252131FF /* Background */, 0xC7EF00FF /* Text */, 0xF4F1DEFF /* MainColor */, 0xDA115EFF /* MainAccent */, 0x792359FF /* Highlight */);
		scheme.apply();

		AssetImporter importer;
		importer.import(AssetLibrary::instance()->getDirectory(), true);

		registerWindows();

		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			const std::unique_ptr<Window>& window = *it;
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
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			const std::unique_ptr<Window>&  window = *it;
			Layout::begin(window->getTitle());
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
		Input::instance()->preventMouseEvents = ImGui::GetIO().WantCaptureMouse;

		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			const std::unique_ptr<Window>& window = *it;
			window->update(deltaTime);
		}
	}
	
	void Editor::registerWindows()
	{
		TypeFactory::load<ContentBrowser>();
		TypeFactory::load<InspectorWindow>();
		TypeFactory::load<Performance>();
		TypeFactory::load<RendererInspector>();
		TypeFactory::load<SceneInspector>();

		static std::set<std::string> types = TypeFactory::listByCategory("Editor");
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