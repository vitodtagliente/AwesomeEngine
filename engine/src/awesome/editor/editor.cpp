#include "editor.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/data/asset_library.h>

#include "asset_importer.h"
#include "color_scheme.h"
#include "layout.h"
#include "window.h"

#include "windows/content_browser.h"
#include "windows/inspector.h"
#include "windows/performance.h"
#include "windows/renderer_inspector.h"
#include "windows/scene_inspector.h"

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
			Window* const window = *it;
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
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			Window* const window = *it;
			window->update(deltaTime);
		}
	}
	
	void Editor::registerWindows()
	{
		addWindow<ContentBrowser>();
		addWindow<Inspector>();
		addWindow<Performance>();
		addWindow<RendererInspector>();
		addWindow<SceneInspector>();
	}
}